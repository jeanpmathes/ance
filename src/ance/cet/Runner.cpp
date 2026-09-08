#include "Runner.h"

#include "Temporary.h"
#include "Variable.h"

#include <algorithm>
#include <expected>
#include <filesystem>
#include <functional>
#include <list>
#include <map>
#include <ranges>
#include <set>
#include <span>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "ance/bbt/Function.h"
#include "ance/bbt/IntrinsicSignature.h"
#include "ance/bbt/Node.h"
#include "ance/bbt/Segmenter.h"
#include "ance/bbt/Type.h"

#include "ance/cet/Grapher.h"
#include "ance/cet/IntrinsicsRunner.h"
#include "ance/cet/Node.h"
#include "ance/cet/Printer.h"
#include "ance/cet/Scope.h"
#include "ance/cet/ValueExtensions.h"

namespace
{
    auto prefix = "runner";
}

struct ance::cet::Runner::Implementation
{
    class BBT final : public bbt::Visitor
    {
      public:
        using Visitor::visit;

        enum class ExecutionResult
        {
            /// The run point has completed execution. Only produced by top-level run points.
            Completed,
            /// The run point is pending on the resolution of a name. Running it directly again will again result in pending.
            Pending,
            /// The run point yielded execution to allow re-entry into itself, e.g. after the function changed. It should be entered again immediately.
            Yield,
            /// The run point encountered an unrecoverable error.
            Error,
        };

        friend std::ostream& operator<<(std::ostream& os, ExecutionResult const result)
        {
            switch (result)
            {
                case ExecutionResult::Completed:
                    os << "Completed";
                    break;
                case ExecutionResult::Pending:
                    os << "Pending";
                    break;
                case ExecutionResult::Yield:
                    os << "Yield";
                    break;
                case ExecutionResult::Error:
                    os << "Error";
                    break;
            }

            return os;
        }

        struct RunPoint
        {
            RunPoint(
                bbt::BasicBlock const&                                     start,
                utility::Optional<utility::Shared<bbt::Type const>> const& type,
                Scope*                                                     initial_scope
            )
                : return_type(type),
                  block(&start),
                  scope(initial_scope)
            {}

            utility::Optional<utility::Shared<bbt::Type const>> return_type;

            bbt::BasicBlock const* block           = nullptr;
            size_t                 statement_index = 0;
            Scope*                 scope           = nullptr;

            utility::Optional<utility::Shared<bbt::Value const>> return_value =
                std::nullopt;

            RunPoint& getExecutableRunPoint()
            {
                if (stack().empty())
                {
                    return *this;
                }

                return stack().back();
            }

            [[nodiscard]] RunPoint const& getExecutableRunPoint() const
            {
                if (stack().empty())
                {
                    return *this;
                }

                return stack().back();
            }

            [[nodiscard]] bool isTopLevel() const
            {
                return stack().empty();
            }

            [[nodiscard]] bool isExecuting() const
            {
                return getExecutableRunPoint().executing_;
            }

            void enter()
            {
                executing_ = true;
                blocker_   = std::nullopt;
            }

            void exit()
            {
                executing_ = false;
            }

            void popLevel(utility::Shared<bbt::Value const> lower_return_value)
            {
                stack().pop_back();

                auto next = this;

                if (!stack().empty())
                {
                    next = &stack().back();
                }

                next->return_value = lower_return_value;
            }

            void pushLevel(
                bbt::BasicBlock const& start,
                utility::Optional<utility::Shared<bbt::Type const>> const&
                       expected_return_type,
                Scope& initial_scope
            ) const
            {
                RunPoint& lower_level =
                    stack().emplace_back(start, expected_return_type, &initial_scope);
                lower_level.target_stack_ = target_stack_;
            }

            [[nodiscard]] utility::Optional<PendingResolution> const& getBlocker() const
            {
                return getExecutableRunPoint().blocker_;
            }

            void setBlocker(PendingResolution const& blocker)
            {
                blocker_ = blocker;
            }

          private:
            [[nodiscard]] std::list<RunPoint>& stack() const
            {
                return *target_stack_;
            }

            // todo: the self-referential nature of this is ugly, split into two types

            std::list<RunPoint>  stack_;
            std::list<RunPoint>* target_stack_ = &stack_;

            utility::Optional<PendingResolution> blocker_   = std::nullopt;
            bool                                 executing_ = false;
        };

        BBT(sources::SourceTree&                                           source_tree,
            core::Reporter&                                                reporter,
            bbt::TypeContext&                                              type_context,
            std::function<utility::Optional<
                utility::Owned<bbt::Flows>>(std::filesystem::path const&)> get_flows)
            : source_tree_(source_tree),
              reporter_(reporter),
              type_context_(type_context),
              read_flows_(std::move(get_flows)),
              core_language_scope_(utility::makeOwned<CoreScope>(type_context)),
              project_scope_(core_language_scope_->addChildScope(
                  utility::makeOwned<UnorderedScope>(*core_language_scope_, type_context)
              ))
        {}

        ~BBT() override = default;

        void schedule(
            bbt::Flow const& flow,
            utility::Optional<utility::Shared<bbt::Type const>> const&
                   expected_return_type,
            Scope* scope
        )
        {
            reporter_.trace(prefix, core::Location::nowhere())
                << "schedule flow {id=" << flow.id() << "}";

            scope = scope != nullptr ? scope : &project_scope_;
            run_points_.emplace_back(flow.entry, expected_return_type, scope);
        }

        void scheduleCore(utility::Owned<bbt::Flow> flow)
        {
            bbt::Flow& flow_ref = *flow;

            core_flows_.emplace_back(std::move(flow));

            schedule(flow_ref, std::nullopt, core_language_scope_.get());
        }

        [[nodiscard]] bool hasExecutableRunPoints() const
        {
            return std::ranges::any_of(run_points_, [](RunPoint const& run_point) {
                return !run_point.isExecuting();
            });
        }

        std::list<RunPoint>::iterator getRunPointBegin()
        {
            return run_points_.begin();
        }

        std::list<RunPoint>::iterator getRunPointEnd()
        {
            return run_points_.end();
        }

        std::list<RunPoint>::iterator removeRunPoint(
            std::list<RunPoint>::iterator const& index
        )
        {
            return run_points_.erase(index);
        }

        void reportBlockers() const
        {
            for (auto const& run_point : run_points_)
            {
                auto const& blocker = run_point.getBlocker();

                if (blocker.hasValue())
                {
                    auto const& [identifier, reason] = blocker.value();

                    auto msg = reporter_.error(identifier.location());
                    msg << "Cannot resolve name " << identifier;

                    if (std::holds_alternative<FindResult::Erased>(reason))
                    {
                        auto const& [erase_location, declaration_location, hides_outer_declaration] =
                            std::get<FindResult::Erased>(reason);

                        if (hides_outer_declaration)
                        {
                            msg << core::Reporter::Annotation(declaration_location)
                                << "Declaration blocks access to " << identifier
                                << " in outer scopes, even after erase";
                        }

                        msg << core::Reporter::Annotation(erase_location) << identifier
                            << " was erased here";
                    }
                }
            }
        }

        std::tuple<ExecutionResult, utility::Shared<bbt::Value const>> execute(
            RunPoint* run_point
        )
        {
            State previous_state = std::move(state_);
            state_               = State(
                run_point->scope,
                run_point,
                run_point->statement_index,
                run_point->block
            );

            run_point->enter();

            reporter_.trace(prefix, core::Location::nowhere())
                << "execute run point enter {block="
                << (state_.next != nullptr ? std::to_string(state_.next->id) : "null")
                << ", statement_index=" << state_.current_statement_index << "}";

            while (!state_.execution_result.hasValue() && state_.next != nullptr)
            {
                run_point->block = state_.next;
                visit(*state_.next);
            }

            run_point->exit();

            run_point->scope           = state_.current_scope;
            run_point->block           = state_.next;
            run_point->statement_index = state_.current_statement_index;

            ExecutionResult const result =
                state_.execution_result.valueOr(ExecutionResult::Completed);
            utility::Shared<bbt::Value const> return_value =
                state_.return_value.valueOr(bbt::Unit::make(type_context_));

            reporter_.trace(prefix, core::Location::nowhere())
                << "execute run point exit {result=" << result
                << ", return_value=" << return_value->toString()
                << ", return_type=" << return_value->type()->name() << "}";

            state_ = std::move(previous_state);

            return {result, return_value};
        }

        ExecutionResult execute(RunPoint& run_point)
        {
            auto [result, return_value] = execute(&run_point.getExecutableRunPoint());

            if (!run_point.isTopLevel() && result == ExecutionResult::Completed)
            {
                result = ExecutionResult::Yield;
                run_point.popLevel(return_value);
            }

            return result;
        }

        [[nodiscard]] bool expectType(
            bbt::Type const&      expected,
            bbt::Type const&      actual,
            core::Location const& location
        ) const
        {
            bool ok = true;

            bbt::Type const& actual_dereferenced = deReferenceType(actual);

            if (actual_dereferenced != expected)
            {
                reporter_.error(location)
                    << "Expected type " << expected.annotated() << " but got "
                    << actual_dereferenced.annotated();
                ok = false;
            }

            return ok;
        }

        [[nodiscard]] bool expectSignature(
            bbt::Signature const&                                          signature,
            std::span<std::reference_wrapper<bbt::Type const> const> const argument_types,
            std::span<core::Location const> const argument_locations,
            core::Location const&                 location
        ) const
        {
            bool ok = true;

            size_t const arity          = signature.arity();
            size_t const argument_count = argument_types.size();

            if (signature.isVariadic())
            {
                if (argument_count < arity)
                {
                    reporter_.error(location)
                        << "Call to " << signature.annotated()
                        << " with too few arguments: expected at least " << arity
                        << " but got " << argument_count;
                    return false;
                }

                for (size_t const index : std::views::iota(size_t {0}, arity))
                {
                    bbt::Type const& parameter_type = *signature.parameters()[index].type;
                    bbt::Type const& argument_type  = argument_types[index].get();
                    core::Location const& argument_location = argument_locations[index];

                    ok &= expectType(parameter_type, argument_type, argument_location);
                }
            }
            else
            {
                if (arity != argument_count)
                {
                    reporter_.error(location)
                        << "Call to " << signature.annotated()
                        << " with wrong number of arguments: expected " << arity
                        << " but got " << argument_count;
                    ok = false;
                }

                if (!ok) return false;

                for (size_t const index : std::views::iota(size_t {0}, argument_count))
                {
                    bbt::Type const& parameter_type = *signature.parameters()[index].type;
                    bbt::Type const& argument_type  = argument_types[index].get();
                    core::Location const& argument_location = argument_locations[index];

                    ok &= expectType(parameter_type, argument_type, argument_location);
                }
            }

            return ok;
        }

        /// Given a value, give a dereferenced value.
        /// If the value is a reference, the referenced value is accessed repeatedly until it is not a reference.
        /// If the value is not a reference, it is returned directly.
        [[nodiscard]] static utility::Shared<bbt::Value const> deReference(
            utility::Shared<bbt::Value const> value
        )
        {
            while (value->type()->isReference())
            {
                auto const&    reference = value->as<Reference>();
                Address const& address   = reference.address();

                value = address.read();
            }

            return value;
        }

        /// The semantics match that of \c deReference , returning the type the method would return given the type of the passed in value.
        /// Essentially, it strips all reference parts around a type.
        [[nodiscard]] static bbt::Type const& deReferenceType(bbt::Type const& type)
        {
            bbt::Type const* current = &type;

            while (current->isReference())
            {
                current = current->getConstructingType(0).get();
            }

            return *current;
        }

        /// Dereference and cast a value in one step.
        template<typename T>
        static T const& deReference(utility::Shared<bbt::Value const> value)
        {
            return deReference(value)->as<T>();
        }

        /// Get a memory location as a reference.
        /// If the memory location already stores a reference, that is returned.
        /// If not, a reference to the memory location is created.
        static utility::Shared<Reference const> asReference(Memory& memory)
        {
            return (memory.type()->isReference() ? memory.read({}) : memory.access())
                .as<Reference>();
        }

        static utility::Optional<utility::Shared<bbt::Type const>> getCommonType(
            std::span<utility::Shared<bbt::Type const>> types
        )
        {
            if (types.empty()) return std::nullopt;

            { // Check whether all types are the same type.
                utility::Shared<bbt::Type const> common_type = types[0];

                if (!std::ranges::all_of(
                        types | std::views::drop(1),
                        [&common_type](auto const& type) { return *type == *common_type; }
                    ))
                    return std::nullopt;

                return common_type;
            }

            // todo: also check conversions to find common type
        }

        bool expectCommonType(
            std::span<utility::Shared<bbt::Type const>>          types,
            utility::Optional<utility::Shared<bbt::Type const>>* common_type,
            core::Location const&                                location
        ) const
        {
            auto result = getCommonType(types);
            if (result.hasValue())
            {
                if (common_type != nullptr) *common_type = std::move(result.value());

                return true;
            }

            utility::List<utility::Shared<bbt::Type const>> unique_types;
            unique_types.reserve(types.size());

            for (auto& type : types)
            {
                if (std::ranges::find(unique_types, type) == unique_types.end())
                {
                    unique_types.emplace_back(type);
                }
            }

            {
                auto msg = reporter_.error(location);
                msg << "Could not find common type for types ";

                for (size_t const index :
                     std::views::iota(size_t {0}, unique_types.size()))
                {
                    if (index == unique_types.size() - 1) msg << " and ";
                    else if (index > 0) msg << ", ";
                    msg << unique_types[index]->annotated();
                }
            }

            return false;
        }

        struct TemporaryOutput
        {
            BBT*                  bbt;
            bbt::Temporary const& temporary;

            friend std::ostream& operator<<(std::ostream& os, TemporaryOutput const& self)
            {
                utility::Shared<bbt::Value const> value =
                    self.bbt->scope().getTemporary(self.temporary).read();
                return os << self.temporary.id() << "={value=" << value->toString()
                          << ", type=" << value->type()->name() << "}";
            }
        };

        TemporaryOutput temp(bbt::Temporary const& temporary)
        {
            return TemporaryOutput {this, temporary};
        }

        // ReSharper disable once CppMemberFunctionMayBeConst
        core::Reporter::MessageBuilder trace(
            std::string_view const link_name,
            bbt::Link const&       link
        )
        {
            auto msg = reporter_.trace(prefix, core::Location::nowhere());
            msg << "visit link " << link_name << " " << link.location << " {block="
                << (state_.next != nullptr ? std::to_string(state_.next->id) : "null")
                << "}";
            return msg;
        }

        // ReSharper disable once CppMemberFunctionMayBeConst
        core::Reporter::MessageBuilder trace(
            std::string_view const statement_name,
            bbt::Statement const&  statement
        )
        {
            auto msg = reporter_.trace(prefix, core::Location::nowhere());
            msg << "visit statement " << statement_name << " " << statement.location
                << " {block="
                << (state_.next != nullptr ? std::to_string(state_.next->id) : "null")
                << ", statement_index=" << state_.current_statement_index << "}";
            return msg;
        }

        void abort()
        {
            reporter_.trace(prefix, core::Location::nowhere()) << "abort execution";

            state_.execution_result = ExecutionResult::Error;
        }

        void block(PendingResolution const& blocker)
        {
            reporter_.trace(prefix, core::Location::nowhere())
                << "block execution pending on " << blocker.identifier;

            state_.execution_result = ExecutionResult::Pending;

            state_.current_run_point->setBlocker(blocker);
        }

        void yield()
        {
            reporter_.trace(prefix, core::Location::nowhere()) << "yield";

            state_.execution_result = ExecutionResult::Yield;
        }

        [[nodiscard]] Scope& scope()
        {
            if (state_.current_scope != nullptr)
            {
                return *state_.current_scope;
            }

            return project_scope_;
        }

        void visit(bbt::Flows const& flows) override
        {
            scheduleFlows(flows);
        }

        void visit(bbt::UnorderedScope const& scope) override
        {
            // todo: this is kinda wrong because it does not know in which flow to place the unordered flow
            assert(false); // todo: that is why we need to change this before we use it

            scheduleUnorderedScope(scope, project_scope_);
        }

        void visit(bbt::Flow const&) override
        {
            assert(false);
        }

        void visit(bbt::BasicBlock const& basic_block) override
        {
            assert(state_.current_run_point != nullptr);

            size_t const statement_count = basic_block.statements.size();

            while (state_.current_statement_index < statement_count)
            {
                visit(*basic_block.statements[state_.current_statement_index]);

                if (state_.execution_result.hasValue()) return;

                state_.current_statement_index += 1;
            }

            state_.current_statement_index = 0;
            visit(*basic_block.link);
        }

        void visit(bbt::ErrorLink const& error_link) override
        {
            trace("ErrorLink", error_link);

            reporter_.error(error_link.location) << "Cannot execute this link";

            abort();
        }

        void visit(bbt::Return const& return_link) override
        {
            trace("Return", return_link) << ", return_value="
                                         << (state_.return_value.hasValue()
                                                 ? state_.return_value.value()->toString()
                                                 : "()");

            // todo: as soon as there is type inference, it would be nice if we get an error for wrong return types
            // todo: especially in obvious cases such as unit function but return 12;

            if (!state_.return_value.hasValue())
            {
                state_.return_value = bbt::Unit::make(type_context_);
            }

            state_.next = nullptr;
        }

        void visit(bbt::Branch const& branch_link) override
        {
            trace("Branch", branch_link)
                << ", true_branch=" << branch_link.true_branch.id
                << ", false_branch=" << branch_link.false_branch.id
                << ", condition=" << temp(branch_link.condition);

            utility::Shared<bbt::Value const> condition =
                deReference(scope().getTemporary(branch_link.condition).read());
            if (!expectType(
                    *type_context_.Bool(),
                    *condition->type(),
                    branch_link.condition.location
                ))
            {
                abort();
                return;
            }

            if (deReference<bbt::Bool>(condition).value())
            {
                state_.next = &branch_link.true_branch;
            }
            else
            {
                state_.next = &branch_link.false_branch;
            }
        }

        void visit(bbt::Jump const& jump_link) override
        {
            trace("Jump", jump_link) << ", target=" << jump_link.target.id;

            state_.next = &jump_link.target;
        }

        void visit(bbt::Switch const& switch_link) override
        {
            trace("Switch", switch_link) << ", condition=" << temp(switch_link.condition)
                                         << ", #cases=" << switch_link.cases.size();

            utility::Shared<bbt::Value const> condition =
                scope().getTemporary(switch_link.condition).read();
            utility::Shared<bbt::Type const> condition_type = condition->type();

            utility::List<utility::Shared<bbt::Value const>> case_patterns = {};
            utility::Optional<core::Location>                default_pattern_location;
            bool                                             has_invalid_case = false;
            for (auto const& current_case : switch_link.cases)
            {
                if (current_case->pattern == nullptr)
                {
                    default_pattern_location = current_case->pattern_location;
                    break;
                }

                utility::Shared<bbt::Value const> value =
                    deReference(scope().getTemporary(*current_case->pattern).read());
                if (!expectType(
                        *condition_type,
                        *value->type(),
                        current_case->pattern->location
                    ))
                {
                    has_invalid_case = true;
                    continue;
                }

                case_patterns.emplace_back(std::move(value));
            }

            if (has_invalid_case)
            {
                abort();
                return;
            }

            if (!default_pattern_location.hasValue())
            {
                // todo: should actually depend on the number of states of type, e.g. for bool two patterns with no default would be fine
                // todo: that should also bring back the countability and abstract and all the other extra checks of old match, but better

                reporter_.error(switch_link.location)
                    << "Match does not cover all possible states of type "
                    << condition_type->annotated();

                abort();
                return;
            }

            if (case_patterns.size() + 1 < switch_link.cases.size())
            {
                for (auto const& unreachable_case :
                     switch_link.cases | std::views::drop(case_patterns.size() + 1))
                {
                    reporter_.warning(unreachable_case->pattern_location)
                        << "Pattern not reachable"
                        << core::Reporter::Annotation(default_pattern_location.value())
                        << "Covered by preceding default pattern";
                }
            }

            for (size_t const index : std::views::iota(size_t {0}, case_patterns.size()))
            {
                utility::Shared<bbt::Value const> current_pattern = case_patterns[index];

                for (size_t const other_index : std::views::iota(size_t {0}, index))
                {
                    utility::Shared<bbt::Value const> other_pattern =
                        case_patterns[other_index];

                    if (other_pattern->equals(*current_pattern))
                    {
                        reporter_.warning(switch_link.cases[index]->pattern_location)
                            << "Pattern not reachable"
                            << core::Reporter::Annotation(
                                   switch_link.cases[other_index]->pattern_location
                               )
                            << "Covered by preceding pattern";

                        break;
                    }
                }
            }

            bbt::BasicBlock const* next = nullptr;

            for (size_t const index :
                 std::views::iota(size_t {0}, switch_link.cases.size()))
            {
                bool const is_default_case = switch_link.cases[index]->pattern == nullptr;

                if (is_default_case || case_patterns[index]->equals(*condition))
                {
                    next = &switch_link.cases[index]->target;

                    break;
                }
            }

            if (next == nullptr)
            {
                throw std::logic_error("Failed to match any case of validated switch");
            }

            state_.next = next;
        }

        void visit(bbt::SwitchCase const&) override
        {
            // Completely handled in visit(bbt::Switch const&) and therefore empty here.
        }

        void visit(bbt::ErrorStatement const& error_statement) override
        {
            trace("ErrorStatement", error_statement);

            reporter_.error(error_statement.location) << "Cannot execute this statement";

            abort();
        }

        void visit(bbt::Pass const& pass_statement) override
        {
            trace("Pass", pass_statement);

            // Intentionally left empty.
        }

        void visit(bbt::Assert const& assert_statement) override
        {
            trace("Assert", assert_statement);

            // todo: assert can be replaced with a function when compiletime exec is good enough
            // todo: in compiletime, it would use an advanced version of the log intrinsic, maybe in combination with a fail intrinsic
            // todo: in runtime, it would call the corresponding function of the language runtime, using a runtime_library_call intrinsic
            // todo: to select the right variant, one could have overloads that just differ in execution mode

            utility::Shared<bbt::Value const> condition =
                deReference(scope().getTemporary(assert_statement.condition).read());
            if (!expectType(
                    *type_context_.Bool(),
                    *condition->type(),
                    assert_statement.condition.location
                ))
            {
                abort();
                return;
            }

            if (!deReference<bbt::Bool>(condition).value())
            {
                reporter_.error(assert_statement.location) << "Assertion failed";
                abort();
            }
        }

        void visit(bbt::Store const& store) override
        {
            trace("Store", store)
                << ", target=" << temp(store.target) << ", value=" << temp(store.value);

            utility::Shared<bbt::Value const> target =
                scope().getTemporary(store.target).read();
            utility::Shared<bbt::Value const> value =
                scope().getTemporary(store.value).read();

            if (!target->type()->isReference()
                || !target->type()->variability().isVariable())
            {
                reporter_.error(store.target.location)
                    << "Can only store to variable reference values";
                abort();
                return;
            }

            // todo: this is not ideal with constants, technically we could get a ref to it when it is not defined yet but then write twice to it through the same ref

            utility::Shared<Reference const> reference = target.as<Reference>();

            if (!expectType(
                    *target->type()->getConstructingType(0),
                    *value->type(),
                    store.value.location
                ))
            {
                abort();
                return;
            }

            reference->address().write(deReference(value));
        }

        void visit(bbt::Access const& access) override
        {
            trace("Access", access) << ", variable=" << access.variable.id()
                                    << ", destination=" << access.destination.id();

            utility::Shared<bbt::Value const> target =
                deReference(scope().getTemporary(access.variable).read());

            if (!expectType(
                    *type_context_.VariableRef(),
                    *target->type(),
                    access.variable.location
                ))
            {
                abort();
                return;
            }

            Variable& variable = target->as<VariableRef>().value();

            // todo: using type inference, we could determine whether we want to later write to it or if not, if yes and final we could output an error here
            // todo: we could also check whether it is already defined if we want to read later, catching reads from undefined variables

            // todo: right now, reading from this ref would be possible even if the variable is not defined

            scope().getTemporary(access.destination).write(variable.access());
        }

        void visit(bbt::Temporary const& temporary) override
        {
            trace("Temporary", temporary) << ", id=" << temporary.id();

            scope().createTemporary(temporary);
        }

        void visit(bbt::Dereference const& dereference) override
        {
            trace("Dereference", dereference)
                << ", target=" << temp(dereference.target)
                << ", destination=" << dereference.destination.id();

            utility::Shared<bbt::Value const> value =
                scope().getTemporary(dereference.target).read();
            scope().getTemporary(dereference.destination).write(deReference(value));
        }

        void visit(bbt::Intrinsic const& intrinsic) override
        {
            if (reporter_.isTraceEnabled())
            {
                auto msg = trace("Intrinsic", intrinsic);
                msg << ", intrinsic=" << intrinsic.intrinsic.toString() << ", args={";

                bool first = true;
                for (auto argument : intrinsic.arguments)
                {
                    if (!first) msg << ", ";
                    else first = false;

                    msg << temp(argument);
                }

                msg << "}, destination=" << intrinsic.destination.id();
            }

            auto [signature, _] =
                bbt::getIntrinsicSignature(intrinsic.intrinsic, type_context_);

            utility::List<std::reference_wrapper<bbt::Type const>> argument_types = {};
            utility::List<core::Location> argument_locations                      = {};

            for (auto argument : intrinsic.arguments)
            {
                utility::Shared<bbt::Value const> value =
                    scope().getTemporary(argument.get()).read();
                argument_types.emplace_back(*value->type());
                argument_locations.emplace_back(argument.get().location);
            }

            if (!expectSignature(
                    signature,
                    argument_types,
                    argument_locations,
                    intrinsic.location
                ))
            {
                abort();
                return;
            }

            utility::List<utility::Shared<bbt::Value const>> arguments = {};

            for (auto argument : intrinsic.arguments)
            {
                utility::Shared<bbt::Value const> value =
                    scope().getTemporary(argument.get()).read();
                arguments.emplace_back(deReference(value));
            }

            auto result =
                intrinsics_.run(intrinsic.intrinsic, arguments, intrinsic.location);

            if (result.isFailed())
            {
                abort();
            }
            else if (result.isPending())
            {
                block(result.getPending());
            }
            else
            {
                scope()
                    .getTemporary(intrinsic.destination)
                    .write(deReference(result.getResult()));
            }
        }

        void visit(bbt::Call const& call) override
        {
            if (reporter_.isTraceEnabled())
            {
                auto msg = trace("Call", call);
                msg << ", called=" << temp(call.called) << ", args={";

                bool first = true;
                for (auto argument : call.arguments)
                {
                    if (!first) msg << ", ";
                    else first = false;

                    msg << temp(argument);
                }

                msg << "}, destination=" << call.destination.id();
            }

            RunPoint& run_point = *state_.current_run_point;

            if (run_point.return_value.hasValue())
            {
                scope()
                    .getTemporary(call.destination)
                    .write(deReference(run_point.return_value.value()));

                run_point.return_value = std::nullopt;

                return;
            }

            utility::Shared<bbt::Value const> called =
                deReference(scope().getTemporary(call.called).read());

            if (!expectType(
                    *type_context_.Function(),
                    *called->type(),
                    call.called.location
                ))
            {
                abort();
                return;
            }

            utility::Shared<bbt::Function const> function  = called.as<bbt::Function>();
            bbt::Signature                       signature = function->signature();

            utility::List<std::reference_wrapper<bbt::Type const>> argument_types = {};
            utility::List<core::Location> argument_locations                      = {};

            for (auto argument : call.arguments)
            {
                utility::Shared<bbt::Value const> value =
                    scope().getTemporary(argument.get()).read();
                argument_types.emplace_back(*value->type());
                argument_locations.emplace_back(argument.get().location);
            }

            if (!expectSignature(
                    signature,
                    argument_types,
                    argument_locations,
                    call.location
                ))
            {
                abort();
                return;
            }

            utility::List<utility::Shared<bbt::Value const>> arguments = {};
            for (auto argument : call.arguments)
            {
                arguments.emplace_back(scope().getTemporary(argument.get()).read());
            }

            Scope& function_scope = project_scope_.addChildScope(
                utility::makeOwned<OrderedScope>(project_scope_, type_context_)
            );

            for (size_t const index : std::views::iota(size_t {0}, signature.arity()))
            {
                bbt::Signature::Parameter&        parameter = signature[index];
                utility::Shared<bbt::Value const> argument  = arguments[index];

                utility::Optional<utility::Shared<bbt::Value const>> variable =
                    function_scope.declare(
                        parameter.name,
                        parameter.type,
                        false,
                        core::Location::project(),
                        reporter_
                    );

                if (!variable.hasValue())
                {
                    abort();
                    return;
                }

                (*variable)->as<VariableRef>().value().write(deReference(argument));
            }

            run_point.pushLevel(
                function->body().entry,
                function->returnType(),
                function_scope
            );

            yield();
        }

        void visit(bbt::Subscript const& subscript) override
        {
            trace("Subscript", subscript)
                << ", indexed=" << temp(subscript.indexed)
                << ", index=" << temp(subscript.index)
                << ", destination=" << subscript.destination.id();

            utility::Shared<Reference const> indexed_reference =
                asReference(scope().getTemporary(subscript.indexed));

            utility::Shared<bbt::Value const> index_value =
                deReference(scope().getTemporary(subscript.index).read());
            if (!expectType(
                    *type_context_.Size(),
                    *index_value->type(),
                    subscript.index.location
                ))
            {
                abort();
                return;
            }

            utility::Shared<bbt::Type const> indexed_type =
                indexed_reference->type()->getConstructingType(0);
            if (!indexed_type->isSubscriptDefined())
            {
                reporter_.error(subscript.indexed.location)
                    << "Cannot subscript value of type " << indexed_type->annotated();
                abort();
                return;
            }

            size_t const index = deReference<bbt::Size>(index_value).value();

            if (!indexed_type->isSubscriptInBounds(index))
            {
                reporter_.error(subscript.index.location)
                    << "Subscript index " << index << " is out of bounds";
                abort();
                return;
            }

            scope()
                .getTemporary(subscript.destination)
                .write(
                    Reference::make(
                        indexed_reference->address().subscript(index),
                        indexed_type->getSubscriptType(),
                        indexed_reference->type()->variability(),
                        type_context_
                    )
                );
        }

        void visit(bbt::FunctionConstructor const& function_constructor) override
        {
            if (reporter_.isTraceEnabled())
            {
                auto msg = trace("FunctionConstructor", function_constructor);
                msg << ", name=" << function_constructor.name << ", parameters={";

                bool first = true;
                for (auto const& param : function_constructor.parameters)
                {
                    if (!first) msg << ", ";
                    else first = false;

                    msg << param.identifier << ": " << temp(param.type);
                }

                msg << "}" << ", return_type=" << temp(function_constructor.return_type)
                    << ", destination=" << function_constructor.destination.id();
            }

            utility::List<bbt::Signature::Parameter>   parameters      = {};
            std::map<core::Identifier, core::Location> seen_parameters = {};
            for (auto const& param : function_constructor.parameters)
            {
                utility::Shared<bbt::Value const> type_value =
                    deReference(scope().getTemporary(param.type).read());
                if (!expectType(
                        *type_context_.Type(),
                        *type_value->type(),
                        param.type.location
                    ))
                {
                    abort();
                    return;
                }

                auto const [previous, inserted] = seen_parameters.emplace(
                    param.identifier,
                    param.identifier.location()
                );
                if (!inserted)
                {
                    reporter_.warning(param.identifier.location())
                        << "Parameter " << param.identifier << " hides earlier parameter"
                        << core::Reporter::Annotation(previous->second)
                        << "Hidden parameter " << param.identifier;
                }

                parameters.emplace_back(param.identifier, type_value.as<bbt::Type>());
            }

            bbt::Signature const signature =
                bbt::Signature(function_constructor.name, std::move(parameters));

            utility::Shared<bbt::Value const> return_type_value = deReference(
                scope().getTemporary(function_constructor.return_type).read()
            );
            if (!expectType(
                    *type_context_.Type(),
                    *return_type_value->type(),
                    function_constructor.return_type.location
                ))
            {
                abort();
                return;
            }

            utility::Shared<bbt::Type const> return_type =
                return_type_value.as<bbt::Type>();

            if (!return_type->equals(*type_context_.Unit())
                && !function_constructor.body->attributes.explicit_return_value_occurrence
                        .isAtLeastOnce())
            {
                reporter_.error(function_constructor.body->location)
                    << "Not all paths return a value";
                abort();
                return;
            }

            utility::Shared<bbt::Function> function = utility::makeShared<bbt::Function>(
                signature,
                return_type,
                *function_constructor.body,
                type_context_
            );

            scope().getTemporary(function_constructor.destination).write(function);
        }

        void visit(bbt::Constant const& constant) override
        {
            trace("Constant", constant) << ", value=" << constant.value->toString()
                                        << ", type=" << constant.value->type()->name()
                                        << ", destination=" << constant.destination.id();

            scope().getTemporary(constant.destination).write(constant.value);
        }

        void visit(bbt::Default const& default_value) override
        {
            trace("Default", default_value)
                << ", type=" << temp(default_value.type)
                << ", destination=" << default_value.destination.id();

            utility::Shared<bbt::Value const> type_value =
                deReference(scope().getTemporary(default_value.type).read());
            if (!expectType(
                    *type_context_.Type(),
                    *type_value->type(),
                    default_value.type.location
                ))
            {
                abort();
                return;
            }

            std::function<
                utility::Shared<bbt::Value const>(utility::Shared<bbt::Type const>)>
                get_default_value = [&](
                                        utility::Shared<bbt::Type const> type
                                    ) -> utility::Shared<bbt::Value const> {
                // todo: should become default constructor call at some point

                if (*type == *type_context_.Bool())
                    return bbt::Bool::make(false, type_context_);
                if (*type == *type_context_.Unit()) return bbt::Unit::make(type_context_);
                if (*type == *type_context_.Size())
                    return bbt::Size::make(0, type_context_);
                if (*type == *type_context_.Location())
                    return bbt::Location::make(core::Location::project(), type_context_);
                if (*type == *type_context_.String())
                    return bbt::String::make("", type_context_);

                if (type->isArray())
                {
                    auto const& array_type   = type->as<bbt::ArrayType>();
                    auto        element_type = type->getConstructingType(0);

                    utility::List<utility::Shared<bbt::Value const>> elements;
                    elements.reserve(array_type.length());

                    std::ranges::for_each(
                        std::views::iota(size_t {0}, array_type.length()),
                        [&](size_t) {
                            elements.emplace_back(get_default_value(element_type));
                        }
                    );

                    return bbt::Array::make(
                        std::move(type),
                        std::move(elements),
                        type_context_
                    );
                }

                // todo: float types

                reporter_.error(default_value.type.location)
                    << "Cannot create default value for type " << type->annotated();

                return bbt::Unit::make(type_context_);
            };

            utility::Shared<bbt::Value const> value =
                get_default_value(type_value.as<bbt::Type>());
            scope().getTemporary(default_value.destination).write(value);
        }

        void visit(bbt::CurrentScope const& current_scope) override
        {
            trace("CurrentScope", current_scope)
                << ", destination=" << current_scope.destination.id();

            scope()
                .getTemporary(current_scope.destination)
                .write(ScopeRef::make(scope(), type_context_));
        }

        void visit(
            bbt::GetUnaryOperatorFunctionIdentifier const&
                get_unary_operator_function_identifier
        ) override
        {
            trace(
                "GetUnaryOperatorFunctionIdentifier",
                get_unary_operator_function_identifier
            ) << ", op="
              << get_unary_operator_function_identifier.op.toString()
              << ", type=" << get_unary_operator_function_identifier.type.id()
              << ", destination="
              << get_unary_operator_function_identifier.destination.id();

            utility::Shared<bbt::Type const> type =
                scope()
                    .getTemporary(get_unary_operator_function_identifier.type)
                    .read()
                    .as<bbt::Type>();

            utility::Optional<core::Identifier> operator_function_identifier =
                type->getUnaryOperatorFunctionIdentifier(
                    get_unary_operator_function_identifier.op
                );

            if (!operator_function_identifier.hasValue())
            {
                reporter_.error(get_unary_operator_function_identifier.location)
                    << "Operator '"
                    << get_unary_operator_function_identifier.op.toString()
                    << "' is not defined for type " << type->annotated();
                abort();
                return;
            }

            scope()
                .getTemporary(get_unary_operator_function_identifier.destination)
                .write(
                    bbt::Identifier::make(
                        operator_function_identifier.value(),
                        type_context_
                    )
                );
        }

        void visit(
            bbt::GetBinaryOperatorFunctionIdentifier const&
                get_binary_operator_function_identifier
        ) override
        {
            trace(
                "GetBinaryOperatorFunctionIdentifier",
                get_binary_operator_function_identifier
            ) << ", op="
              << get_binary_operator_function_identifier.op.toString()
              << ", left_type=" << get_binary_operator_function_identifier.left_type.id()
              << ", right_type="
              << get_binary_operator_function_identifier.right_type.id()
              << ", destination="
              << get_binary_operator_function_identifier.destination.id();

            utility::Shared<bbt::Type const> left_type =
                scope()
                    .getTemporary(get_binary_operator_function_identifier.left_type)
                    .read()
                    .as<bbt::Type>();
            utility::Shared<bbt::Type const> right_type =
                scope()
                    .getTemporary(get_binary_operator_function_identifier.right_type)
                    .read()
                    .as<bbt::Type>();

            utility::Optional<core::Identifier> operator_function_identifier =
                left_type->getBinaryOperatorFunctionIdentifier(
                    get_binary_operator_function_identifier.op,
                    *right_type
                );

            if (!operator_function_identifier.hasValue())
            {
                reporter_.error(get_binary_operator_function_identifier.location)
                    << "Operator '"
                    << get_binary_operator_function_identifier.op.toString()
                    << "' is not defined for type " << left_type->annotated();
                abort();
                return;
            }

            scope()
                .getTemporary(get_binary_operator_function_identifier.destination)
                .write(
                    bbt::Identifier::make(
                        operator_function_identifier.value(),
                        type_context_
                    )
                );
        }

        void visit(bbt::TypeOf const& type_of) override
        {
            if (reporter_.isTraceEnabled())
            {
                auto msg = trace("TypeOf", type_of);
                msg << "values={";

                bool first = true;
                for (auto& value : type_of.values)
                {
                    if (!first) msg << ", ";
                    else first = false;

                    msg << temp(value);
                }

                msg << ", destination=" << type_of.destination.id();
            }

            utility::List<utility::Shared<bbt::Type const>> types;
            for (auto const& expression : type_of.values)
            {
                types.emplace_back(scope().getTemporary(expression.get()).read()->type());
            }

            utility::Optional<utility::Shared<bbt::Type const>> common_type;
            if (expectCommonType(types, &common_type, type_of.location))
            {
                scope().getTemporary(type_of.destination).write(*common_type);
            }
            else
            {
                abort();
            }
        }

        void visit(bbt::ArrayTypeConstructor const& array_type) override
        {
            trace("ArrayType", array_type)
                << ", element_type=" << temp(array_type.element_type)
                << ", length=" << temp(array_type.length)
                << ", destination=" << array_type.destination.id();

            utility::Shared<bbt::Value const> element_type_value =
                deReference(scope().getTemporary(array_type.element_type).read());
            if (!expectType(
                    *type_context_.Type(),
                    *element_type_value->type(),
                    array_type.element_type.location
                ))
            {
                abort();
                return;
            }

            utility::Shared<bbt::Value const> length_value =
                deReference(scope().getTemporary(array_type.length).read());
            if (!expectType(
                    *type_context_.Size(),
                    *length_value->type(),
                    array_type.length.location
                ))
            {
                abort();
                return;
            }

            utility::Shared<bbt::Type const> element_type =
                element_type_value.as<bbt::Type>();
            size_t const length = deReference<bbt::Size>(length_value).value();

            scope()
                .getTemporary(array_type.destination)
                .write(type_context_.Array(std::move(element_type), length));
        }

        void visit(bbt::ArrayConstructor const& array_constructor) override
        {
            if (reporter_.isTraceEnabled())
            {
                auto msg = trace("ArrayConstructor", array_constructor);
                msg << ", element_type=";

                if (array_constructor.element_type != nullptr)
                    msg << temp(*array_constructor.element_type);
                else msg << "inferred";

                msg << ", elements={";

                bool first = true;
                for (auto element : array_constructor.elements)
                {
                    if (!first) msg << ", ";
                    else first = false;

                    msg << temp(element);
                }

                msg << "}, destination=" << array_constructor.destination.id();
            }

            if (array_constructor.elements.empty()
                && array_constructor.element_type == nullptr)
            {
                // todo: once type inference exists, '[]' should be allowed

                reporter_.error(array_constructor.location)
                    << "Cannot infer element type of empty array constructor";
                abort();
                return;
            }

            utility::Optional<utility::Shared<bbt::Type const>> element_type;
            if (array_constructor.element_type != nullptr)
            {
                utility::Shared<bbt::Value const> element_type_value = deReference(
                    scope().getTemporary(*array_constructor.element_type).read()
                );
                if (!expectType(
                        *type_context_.Type(),
                        *element_type_value->type(),
                        array_constructor.element_type->location
                    ))
                {
                    abort();
                    return;
                }

                element_type = element_type_value.as<bbt::Type>();
            }

            utility::List<utility::Shared<bbt::Value const>> elements;
            utility::List<utility::Shared<bbt::Type const>>  element_types;

            for (auto const& element : array_constructor.elements)
            {
                utility::Shared<bbt::Value const> value =
                    deReference(scope().getTemporary(element.get()).read());

                elements.emplace_back(value);
                element_types.emplace_back(value->type());
            }

            if (!element_type.hasValue()
                && !expectCommonType(
                    element_types,
                    &element_type,
                    array_constructor.location
                ))
            {
                abort();
                return;
            }

            assert(element_type.hasValue());

            for (size_t const index : std::views::iota(size_t {0}, elements.size()))
            {
                if (!expectType(
                        *element_type.value(),
                        *elements[index]->type(),
                        array_constructor.elements[index].get().location
                    ))
                {
                    abort();
                    return;
                }
            }

            utility::Shared<bbt::Type const> array_type =
                type_context_.Array(element_type.value(), elements.size());
            scope()
                .getTemporary(array_constructor.destination)
                .write(
                    bbt::Array::make(
                        std::move(array_type),
                        std::move(elements),
                        type_context_
                    )
                );
        }

        void visit(bbt::OrderedScopeEnter const& scope_enter) override
        {
            trace("OrderedScopeEnter", scope_enter);

            state_.current_scope = &scope().addChildScope(
                utility::makeOwned<OrderedScope>(scope(), type_context_)
            );
        }

        void visit(bbt::OrderedScopeExit const& scope_exit) override
        {
            trace("OrderedScopeExit", scope_exit);

            Scope& child_scope = scope();

            state_.current_scope = child_scope.parent();
            state_.current_scope->removeChildScope(child_scope);

            // todo: destructors and stuff, clean up value storage
        }

        void visit(bbt::SetReturnValue const& set_return_value) override
        {
            trace("SetReturnValue", set_return_value)
                << ", value=" << temp(set_return_value.value);

            assert(!state_.return_value.hasValue());

            utility::Shared<bbt::Value const> value =
                deReference(scope().getTemporary(set_return_value.value).read());
            if (state_.current_run_point->return_type.hasValue())
            {
                bool const ok = expectType(
                    *state_.current_run_point->return_type.value(),
                    *value->type(),
                    set_return_value.value.location
                );
                (void) ok; // We assign anyway so that later checks are not confused.
            }
            state_.return_value = value;
        }

        void declareCoreVariable(
            core::Identifier const&           name,
            utility::Shared<bbt::Value const> value
        )
        {
            value = deReference(std::move(value));

            FindResult const result = core_language_scope_->find(name);
            if (result.status == FindResult::Status::FOUND && result.value.hasValue())
            {
                return; // todo: generally, we would want to throw in this case, but for now that is not possible
            }

            utility::Optional<utility::Shared<bbt::Value const>> declared =
                core_language_scope_->declare(
                    name,
                    value->type(),
                    false,
                    core::Location::core(),
                    reporter_
                );

            if (declared.hasValue())
                (*declared)->as<VariableRef>().value().write(std::move(value));
        }

        utility::Shared<bbt::Value const> getCoreVariableValue(
            core::Identifier const& name
        )
        {
            FindResult result = core_language_scope_->find(name);

            if (result.status != FindResult::Status::FOUND || !result.value.hasValue())
            {
                throw std::out_of_range(
                    "Core variable not found: '" + std::string(name.text()) + "'"
                );
            }

            return deReference(result.value.value()->as<VariableRef>().value().read());
        }

      private:
        sources::SourceTree& source_tree_;
        core::Reporter&      reporter_;
        bbt::TypeContext&    type_context_;
        std::function<
            utility::Optional<utility::Owned<bbt::Flows>>(std::filesystem::path const&)>
            read_flows_;

        void scheduleFlows(bbt::Flows const& flows)
        {
            for (auto const& flow : flows.flows)
            {
                schedule(*flow, std::nullopt, &project_scope_);
            }
        }

        void scheduleUnorderedScope(bbt::UnorderedScope const& scope, Scope& parent_scope)
        {
            Scope& unordered_scope = parent_scope.addChildScope(
                utility::makeOwned<UnorderedScope>(parent_scope, type_context_)
            );

            for (auto const& flow : scope.flows)
            {
                schedule(*flow, std::nullopt, &unordered_scope);
            }
        }

        std::function<void(std::filesystem::path const&)> include_ =
            [this](std::filesystem::path const& path) {
                utility::Optional<utility::Owned<bbt::Flows>> flows = read_flows_(path);

                if (!flows.hasValue())
                {
                    abort();
                    return;
                }

                bbt::Flows const& flows_ref = **flows;

                included_flows_.emplace_back(std::move(*flows));

                scheduleFlows(flows_ref);
            };

        IntrinsicsRunner intrinsics_ {source_tree_, reporter_, type_context_, include_};

        std::list<RunPoint>                       run_points_     = {};
        utility::List<utility::Owned<bbt::Flow>>  core_flows_     = {};
        utility::List<utility::Owned<bbt::Flows>> included_flows_ = {};

        utility::Owned<CoreScope> core_language_scope_;
        Scope&                    project_scope_;

        struct State
        {
            RunPoint* current_run_point       = nullptr;
            size_t    current_statement_index = 0;
            Scope*    current_scope           = nullptr;

            bbt::BasicBlock const* next = nullptr;

            utility::Optional<utility::Shared<bbt::Value const>> return_value =
                std::nullopt;
            utility::Optional<ExecutionResult> execution_result = std::nullopt;

            State() = default;

            State(
                Scope*                 scope,
                RunPoint*              run_point,
                size_t const           statement_index,
                bbt::BasicBlock const* next_block
            )
                : current_run_point(run_point),
                  current_statement_index(statement_index),
                  current_scope(scope),
                  next(next_block)
            {}
        };

        State state_;
    };

    explicit Implementation(
        sources::SourceTree& source_tree,
        core::Reporter&      reporter,
        core::Context&       context,
        Runner&              runner
    )
        : source_tree_(source_tree),
          reporter_(reporter),
          type_context_(runner),
          segmenter_(source_tree, reporter, context, type_context_),
          context_(context),
          bbt_(
              utility::makeOwned<BBT>(
                  source_tree_,
                  reporter_,
                  type_context_,
                  [&](std::filesystem::path const& f) { return readUnorderedFile(f); }
              )
          )
    {}

    bool run(BBT& bbt)
    {
        reporter_.trace(prefix, core::Location::project()) << "enter run";

        while (bbt.hasExecutableRunPoints())
        {
            bool progress = false;

            for (auto iterator = bbt.getRunPointBegin();
                 iterator != bbt.getRunPointEnd();)
            {
                BBT::RunPoint& run_point = *iterator;

                if (run_point.isExecuting())
                {
                    iterator = std::next(iterator);

                    continue;
                }

                BBT::ExecutionResult const result = bbt.execute(run_point);

                if (result == BBT::ExecutionResult::Completed)
                {
                    iterator = bbt.removeRunPoint(iterator);
                    progress = true;

                    continue;
                }

                if (result == BBT::ExecutionResult::Pending)
                {
                    iterator = std::next(iterator);

                    continue;
                }

                if (result == BBT::ExecutionResult::Yield)
                {
                    progress = true;

                    // It is intentional that we do not advance the iterator here, as the run point should be re-entered immediately.
                    // A yield generally indicates that a function is being called, which means that progress is being made.

                    continue;
                }

                if (result == BBT::ExecutionResult::Error)
                {
                    reporter_.trace(prefix, core::Location::project())
                        << "exit run {status=error}";

                    return false;
                }
            }

            if (!progress && bbt.hasExecutableRunPoints())
            {
                bbt.reportBlockers();

                reporter_.trace(prefix, core::Location::project())
                    << "exit run {status=blocked}";

                return false;
            }
        }

        reporter_.trace(prefix, core::Location::project())
            << "exit run {status=complete}";

        return true;
    }

    utility::Optional<utility::Owned<Unit>> runProjectFile(
        std::filesystem::path const& file
    )
    {
        reporter_.trace(prefix, core::Location::nowhere())
            << "run project file enter {file='" << file.string() << "'}";

        utility::Optional<utility::Owned<bbt::Flow>> flow =
            segmenter_.segmentOrderedFile(file);
        if (!flow.hasValue())
        {
            reporter_.trace(prefix, core::Location::nowhere())
                << "run project file exit {file='" << file.string()
                << "', status=no-segment}";

            return std::nullopt;
        }

        bbt_->schedule(**flow, std::nullopt, nullptr);

        bool const ok = run(*bbt_);

        if (!ok)
        {
            reporter_.trace(prefix, core::Location::nowhere())
                << "run project file exit {file='" << file.string()
                << "', status=fail-run}";

            return std::nullopt;
        }

        utility::Owned<Unit> unit = utility::makeOwned<Unit>();

        context_.print<Printer>(*unit, "cet", file);
        context_.graph<Grapher>(*unit, "cet", file);

        if (reporter_.isFailed())
        {
            reporter_.trace(prefix, core::Location::nowhere())
                << "run project file exit {file='" << file.string()
                << "', status=fail-validate}";

            return std::nullopt;
        }

        return unit;
    }

    utility::Optional<utility::Owned<bbt::Flows>> readUnorderedFile(
        std::filesystem::path const& file
    )
    {
        return segmenter_.segmentUnorderedFile(file);
    }

    void declareCoreVariable(
        core::Identifier const&           name,
        utility::Shared<bbt::Value const> value
    )
    {
        bbt_->declareCoreVariable(name, value);
    }

    utility::Shared<bbt::Value const> getCoreVariableValue(core::Identifier const& name)
    {
        return bbt_->getCoreVariableValue(name);
    }

    void declareCore(std::string const& code, std::string const& id)
    {
        reporter_.trace(prefix, core::Location::nowhere())
            << "declare core enter {id=" << id << "}";

        utility::Optional<utility::Owned<bbt::Flow>> flow =
            segmenter_.segmentDeclaration(code, id);

        if (!flow.hasValue())
        {
            reporter_.trace(prefix, core::Location::nowhere())
                << "declare core exit {id=" << id << ", status=no-segment}";

            throw std::runtime_error("Failed to parse embedded core declaration");
        }

        bbt_->scheduleCore(std::move(flow.value()));

        reporter_.trace(prefix, core::Location::nowhere())
            << "declare core exit {id=" << id << ", status=ok}";
    }

    bbt::TypeContext& getTypeContext()
    {
        return type_context_;
    }

  private:
    sources::SourceTree& source_tree_;
    core::Reporter&      reporter_;
    bbt::TypeContext     type_context_;
    bbt::Segmenter       segmenter_;
    core::Context&       context_;

    utility::Owned<BBT> bbt_;
};

ance::cet::Runner::Runner(
    sources::SourceTree& source_tree,
    core::Reporter&      reporter,
    core::Context&       context
)
    : implementation_(
          utility::makeOwned<Implementation>(source_tree, reporter, context, *this)
      )
{}

ance::cet::Runner::~Runner() = default;

void ance::cet::Runner::declareCoreVariable(
    core::Identifier const&           name,
    utility::Shared<bbt::Value const> value
)
{
    return implementation_->declareCoreVariable(name, std::move(value));
}

ance::utility::Shared<ance::bbt::Value const> ance::cet::Runner::getCoreVariableValue(
    core::Identifier const& name
)
{
    return implementation_->getCoreVariableValue(name);
}

void ance::cet::Runner::declareCore(std::string const& code, std::string const& id)
{
    return implementation_->declareCore(code, id);
}

ance::utility::Optional<ance::utility::Owned<ance::cet::Unit>> ance::cet::Runner::
    runProjectFile(std::filesystem::path const& file)
{
    return implementation_->runProjectFile(file);
}

ance::bbt::TypeContext& ance::cet::Runner::types()
{
    return implementation_->getTypeContext();
}
