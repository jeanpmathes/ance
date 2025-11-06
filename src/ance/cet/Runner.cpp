#include "Runner.h"

#include <iostream>
#include <map>
#include <set>
#include <expected>
#include <string>
#include <functional>
#include <filesystem>
#include <vector>
#include <list>

#include "ance/core/Intrinsic.h"

#include "ance/bbt/Function.h"
#include "ance/bbt/Node.h"
#include "ance/bbt/Segmenter.h"

#include "ance/cet/Node.h"
#include "ance/cet/Provider.h"
#include "ance/cet/Grapher.h"
#include "ance/cet/Printer.h"
#include "ance/cet/Scope.h"
#include "ance/cet/IntrinsicsRunner.h"
#include "ance/cet/ValueExtensions.h"

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

        struct RunPoint
        {
            RunPoint(bbt::BasicBlock const& start, Scope* initial_scope)
                : block(&start), scope(initial_scope)
            {
            }

            void clearBlocker()
            {
                blocker = std::nullopt;
            }

            bbt::BasicBlock const*                 block = nullptr;
            size_t                       statement_index = 0;
            Scope*                                 scope = nullptr;
            utility::Optional<PendingResolution> blocker = std::nullopt;

            std::list<RunPoint>                             stack        = {};
            utility::Optional<utility::Shared<bbt::Value>> return_value = std::nullopt;
        };

        BBT(
            sources::SourceTree& source_tree,
            core::Reporter& reporter,
            std::function<utility::Optional<utility::Owned<bbt::UnorderedScope>>(std::filesystem::path const&)> get_unordered_scope,
            utility::List<utility::Owned<Provider>>& providers)
        : source_tree_(source_tree), reporter_(reporter), read_unordered_scope_(std::move(get_unordered_scope)), providers_(providers) {}
        ~BBT() override = default;

        void schedule(bbt::Flow const& flow, Scope* scope)
        {
            run_points_.emplace_back(flow.entry, scope);
        }

        [[nodiscard]] bool hasRunPoints() const
        {
            return !run_points_.empty();
        }

        std::list<RunPoint>::iterator getRunPointBegin()
        {
            return run_points_.begin();
        }

        std::list<RunPoint>::iterator getRunPointEnd()
        {
            return run_points_.end();
        }

        std::list<RunPoint>::iterator removeRunPoint(std::list<RunPoint>::iterator const& index)
        {
            return run_points_.erase(index);
        }

        void reportBlockers() const
        {
            for (auto const& run_point : run_points_)
            {
                if (run_point.blocker.hasValue())
                {
                    auto const& [identifier] = run_point.blocker.value();
                    reporter_.error("Cannot resolve name '" + identifier + "'", identifier.location());
                }
            }
        }

        std::tuple<ExecutionResult, utility::Shared<bbt::Value>> execute(RunPoint* run_point)
        {
            State const previous_state = state_;

            state_ = State
            {
                .current_run_point = run_point,
                .current_statement_index = run_point->statement_index,
                .next = run_point->block,
                .execution_result = std::nullopt,
                .current_scope = run_point->scope,
            };

            run_point->clearBlocker();

            while (!state_.execution_result.hasValue() && state_.next != nullptr)
            {
                run_point->block = state_.next;
                visit(*state_.next);
            }

            run_point->scope = state_.current_scope;
            run_point->block = state_.next;
            run_point->statement_index = state_.current_statement_index;

            ExecutionResult const result = state_.execution_result.valueOr(ExecutionResult::Completed);

            state_ = previous_state;

            return {result, bbt::UnitValue::make()};
        }

        ExecutionResult execute(RunPoint& run_point)
        {
            RunPoint* targeted_run_point = &run_point;
            bool is_top_level = true;

            if (!run_point.stack.empty())
            {
                targeted_run_point = &run_point.stack.back();
                is_top_level = false;
            }

            auto [result, return_value] = execute(targeted_run_point);

            if (!is_top_level && result == ExecutionResult::Completed)
            {
                run_point.stack.pop_back();
                result = ExecutionResult::Yield;

                RunPoint* next = &run_point;
                if (!run_point.stack.empty())
                {
                    next = &run_point.stack.back();
                }

                next->return_value = return_value;
            }

            return result;
        }

        [[nodiscard]] bool requireType(core::Type const& expected, core::Type const& actual, core::Location const& location) const
        {
            bool ok = true;

            if (expected != actual)
            {
                reporter_.error("Expected type '" + expected.name() + "' but got '" + actual.name() + "'", location);
                ok = false;
            }

            return ok;
        }

        [[nodiscard]] bool requireSignature(core::Signature const& signature, utility::List<std::reference_wrapper<bbt::Temporary const>> const& arguments, core::Location const& location) const
        {
            bool ok = true;

            size_t const arity = signature.arity();
            size_t const argument_count = arguments.size();

            if (arity != argument_count)
            {
                reporter_.error("Call to '" + signature.name() + "' with wrong number of arguments:" +
                                " expected " + std::to_string(arity) +
                                " but got " + std::to_string(argument_count),
                                location);
                ok = false;
            }

            if (!ok) return false;

            for (size_t i = 0; i < argument_count; ++i)
            {
                auto const& argument = arguments[i];
                auto const& argument_value = temporaries_.at(&argument.get());
                auto const& type = signature.parameters()[i].type.get();

                ok &= requireType(type, argument_value->type(), argument.get().location);
            }

            return ok;
        }

        void abort()
        {
            state_.execution_result = ExecutionResult::Error;

            state_.current_run_point->clearBlocker();
        }

        void block(PendingResolution const& blocker)
        {
            state_.execution_result = ExecutionResult::Pending;

            state_.current_run_point->blocker = blocker;
        }

        void yield()
        {
            state_.execution_result = ExecutionResult::Yield;

            state_.current_run_point->clearBlocker();
        }

        [[nodiscard]] Scope* scope() const
        {
            return state_.current_scope;
        }

        void visit(bbt::UnorderedScope const& scope) override
        {
            scheduleUnorderedScope(scope);
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
            reporter_.error("Cannot execute this link", error_link.location);

            abort();
        }

        void visit(bbt::Return const&) override
        {
            state_.next = nullptr;
        }

        void visit(bbt::Branch const& branch_link) override
        {
            utility::Shared<bbt::Value> condition = temporaries_.at(&branch_link.condition);

            if (!requireType(core::Type::Bool(), condition->type(), branch_link.condition.location))
            {
                abort();
                return;
            }

            if (condition->as<bbt::BoolValue>().value())
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
            state_.next = &jump_link.target;
        }

        void visit(bbt::ErrorStatement const& error_statement) override
        {
            reporter_.error("Cannot execute this statement", error_statement.location);

            abort();
        }

        void visit(bbt::Pass const&) override
        {
            // Intentionally left empty.
        }

        void visit(bbt::Store const& store) override
        {
            utility::Shared<bbt::Value> target = temporaries_.at(&store.target);
            utility::Shared<bbt::Value> value = temporaries_.at(&store.value);

            if (!requireType(core::Type::EntityRef(), target->type(), store.target.location))
            {
                abort();
                return;
            }

            core::Entity const& entity = target->as<bbt::EntityRefValue>().value();

            if (entity.asVariable() == nullptr)
            {
                reporter_.error("Cannot store to non-variable entity '" + entity.name() + "'", store.target.location);
                abort();
                return;
            }

            core::Variable const* variable = entity.asVariable();

            bool const is_defined = variables_.contains(&entity);

            if (variable->isFinal() && is_defined)
            {
                reporter_.error("Cannot store to final variable '" + entity.name() + "'", store.target.location);
                abort();
                return;
            }

            core::Type const& type = variable->type(); // todo: use a type method on Entity to get the type

            if (!requireType(type, value->type(), store.value.location))
            {
                abort();
                return;
            }

            variables_.insert_or_assign(&entity, value);
        }

        void visit(bbt::Temporary const& temporary) override
        {
            utility::Shared<bbt::Value> value = bbt::UnitValue::make();
            temporaries_.insert_or_assign(&temporary, value);
        }

        void visit(bbt::CopyTemporary const& write_temporary) override
        {
            utility::Shared<bbt::Value> value = temporaries_.at(&write_temporary.source);
            temporaries_.insert_or_assign(&write_temporary.destination, value);
        }

        void visit(bbt::Intrinsic const& intrinsic) override
        {
            if (!requireSignature(intrinsic.intrinsic.signature(), intrinsic.arguments, intrinsic.location))
            {
                abort();
                return;
            }

            utility::List<utility::Shared<bbt::Value>> arguments = {};

            for (auto argument : intrinsic.arguments) { arguments.emplace_back(temporaries_.at(&argument.get())); }

            auto result = intrinsics_.run(intrinsic.intrinsic, arguments, intrinsic.location);

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
                temporaries_.insert_or_assign(&intrinsic.destination, result.getResult());
            }
        }

        void visit(bbt::Call const& call) override
        {
            RunPoint& run_point = *state_.current_run_point;

            if (run_point.return_value.hasValue())
            {
                temporaries_.insert_or_assign(&call.destination, run_point.return_value.value());
                run_point.return_value = std::nullopt;

                return;
            }

            utility::Shared<bbt::Value> called = temporaries_.at(&call.called);

            if (!requireType(core::Type::EntityRef(), called->type(), call.called.location))
            {
                abort();
                return;
            }

            core::Entity const& entity = called->as<bbt::EntityRefValue>().value();

            // todo: this is currently ugly, because having Function and Variable both be Entities is weird
            // todo: the better way would be to expand calls to be a resolve of a variable, a read from that variable, and then a unary operation call on that value

            if (entity.asFunction() == nullptr)
            {
                reporter_.error("Cannot call non-function entity '" + entity.name() + "'", call.called.location);
                abort();
                return;
            }

            bbt::Function const& function = *static_cast<bbt::Function const*>(entity.asFunction());

            if (!requireSignature(function.signature(), call.arguments, call.location))
            {
                abort();
                return;
            }

            utility::List<utility::Shared<bbt::Value>> arguments = {};
            for (auto argument : call.arguments) { arguments.emplace_back(temporaries_.at(&argument.get())); }

            Scope* function_scope = scopes_.emplace_back(utility::makeOwned<OrderedScope>(this->scope())).get();

            for (size_t i = 0; i < function.signature().arity(); ++i)
            {
                core::Signature::Parameter const& parameter = function.signature().parameters()[i];
                utility::Shared<bbt::Value>& argument = arguments[i];

                utility::Optional<utility::Shared<bbt::Value>> variable = function_scope->declare(parameter.name, parameter.type, true, core::Location::global(), reporter_);

                if (!variable.hasValue())
                {
                    abort();
                    return;
                }

                variables_.insert_or_assign(&(*variable)->as<bbt::EntityRefValue>().value(), argument);
            }

            run_point.stack.emplace_back(function.body().entry, function_scope);

            yield();
        }

        void visit(bbt::Read const& read) override
        {
            utility::Shared<bbt::Value> target = temporaries_.at(&read.target);

            if (!requireType(core::Type::EntityRef(), target->type(), read.target.location))
            {
                abort();
                return;
            }

            core::Entity const& entity = target->as<bbt::EntityRefValue>().value();

            if (entity.asVariable() == nullptr) // todo: this is currently ugly, because having Function and Variable both be Entities is weird
            {
                reporter_.error("Cannot read from non-variable entity '" + entity.name() + "'", read.target.location);
                abort();
                return;
            }

            bool const is_defined = variables_.contains(&entity);
            if (!is_defined)
            {
                reporter_.error("Reading from undefined variable '" + entity.name() + "'", read.target.location);
                abort();
                return;
            }

            utility::Shared<bbt::Value> value = variables_.at(&entity);
            temporaries_.insert_or_assign(&read.destination, value);
        }

        void visit(bbt::Constant const& constant) override
        {
            temporaries_.insert_or_assign(&constant.destination, constant.value->clone());
        }

        void visit(bbt::Default const& default_value) override
        {
            utility::Shared<bbt::Value> type_value = temporaries_.at(&default_value.type);

            if (!requireType(core::Type::Self(), type_value->type(), default_value.type.location))
            {
                abort();
                return;
            }

            auto get_default_value = [&](core::Type const& type) -> utility::Shared<bbt::Value> {
                // todo: should become default constructor call at some point

                if (type == core::Type::Bool()) return bbt::BoolValue::make(false);
                if (type == core::Type::Unit()) return bbt::UnitValue::make();
                if (type == core::Type::Size()) return bbt::SizeValue::make(0);
                if (type == core::Type::Location()) return bbt::LocationValue::make(core::Location::global());
                if (type == core::Type::String()) return bbt::StringValue::make("");

                reporter_.error("Cannot create default value for type '" + type.name() + "'", default_value.type.location);

                return bbt::UnitValue::make();
            };

            utility::Shared<bbt::Value> value = get_default_value(type_value->as<bbt::TypeValue>().value());
            temporaries_.insert_or_assign(&default_value.destination, value);
        }

        void visit(bbt::CurrentScope const& current_scope) override
        {
            assert(this->scope() != nullptr);

            temporaries_.insert_or_assign(&current_scope.destination, ScopeValue::make(*this->scope()));
        }

        void visit(bbt::UnaryOperation const& unary_operation) override
        {
            utility::Shared<bbt::Value> value = temporaries_.at(&unary_operation.operand);

            if (!requireType(core::Type::Bool(), value->type(), unary_operation.operand.location))
            {
                abort();
                return;
            }

            switch (unary_operation.op)
            {
                case core::UnaryOperator::NOT:
                    temporaries_.insert_or_assign(&unary_operation.destination, bbt::BoolValue::make(!value->as<bbt::BoolValue>().value()));
                    break;
            }
        }

        void visit(bbt::TypeOf const& type_of) override
        {
            utility::Shared<bbt::Value> value = temporaries_.at(&type_of.expression);
            temporaries_.insert_or_assign(&type_of.destination, bbt::TypeValue::make(value->type()));
        }

        void visit(bbt::OrderedScopeEnter const&) override
        {
            state_.current_scope = scopes_.emplace_back(utility::makeOwned<OrderedScope>(this->scope())).get();

            // todo: associate the value storage with the scope so that context switch works better
        }

        void visit(bbt::OrderedScopeExit const&) override
        {
            state_.current_scope = scope()->parent();

            // todo: destructors and stuff, clean up value storage
            // todo: maybe deleting the scope instance is a good idea?
        }

      private:
        sources::SourceTree& source_tree_;
        core::Reporter& reporter_;
        std::function<utility::Optional<utility::Owned<bbt::UnorderedScope>>(std::filesystem::path const&)> read_unordered_scope_;
        utility::List<utility::Owned<Provider>>& providers_;

        std::function<utility::Optional<utility::Shared<bbt::Value>>(core::Identifier const&)> provide_ = [this](core::Identifier const& identifier) -> utility::Optional<utility::Shared<bbt::Value>> {
            for (auto& provider : this->providers_)
            {
                core::Entity const* entity = provider->provide(identifier);
                if (entity != nullptr)
                    return bbt::EntityRefValue::make(*entity);
            }

            return std::nullopt;
        };

        void scheduleUnorderedScope(bbt::UnorderedScope const& scope)
        {
            Scope* unordered_scope = scopes_.emplace_back(utility::makeOwned<UnorderedScope>(nullptr)).get();

            for (auto const& flow : scope.flows)
            {
                schedule(*flow, unordered_scope);
            }
        }

        std::function<void(std::filesystem::path const&)> include_ = [this](std::filesystem::path const& path) {
            utility::Optional<utility::Owned<bbt::UnorderedScope>> scope = read_unordered_scope_(path);

            if (!scope.hasValue())
            {
                abort();
                return;
            }

            bbt::UnorderedScope const& scope_ref = **scope;

            roots_.emplace_back(std::move(*scope));

            scheduleUnorderedScope(scope_ref);
        };

        IntrinsicsRunner intrinsics_ {source_tree_, reporter_, provide_, include_};

        std::map<core::Entity const*, utility::Shared<bbt::Value>> variables_ = {};
        std::map<bbt::Temporary const*, utility::Shared<bbt::Value>> temporaries_ = {};

        std::list<RunPoint> run_points_ = {};
        utility::List<utility::Owned<bbt::UnorderedScope>> roots_;
        std::vector<utility::Owned<Scope>> scopes_ = {};

        struct State
        {
            RunPoint* current_run_point = nullptr;
            size_t current_statement_index = 0;

            bbt::BasicBlock const* next = nullptr;
            utility::Optional<ExecutionResult> execution_result = std::nullopt;
            Scope* current_scope = nullptr;
        };

        State state_;
    };

    explicit Implementation(sources::SourceTree& source_tree, core::Reporter& reporter, core::Context& context)
        : source_tree_(source_tree), reporter_(reporter), segmenter_(source_tree, reporter, context), context_(context)
    {}

    utility::Optional<utility::Owned<Unit>> runOrderedFile(std::filesystem::path const& file)
    {
        utility::Optional<utility::Owned<bbt::Flow>> flow = segmenter_.segmentOrderedFile(file);
        if (!flow.hasValue())
            return std::nullopt;

        utility::Owned<BBT> bbt = utility::makeOwned<BBT>(source_tree_, reporter_, [&](std::filesystem::path const& f) { return readUnorderedScope(f); }, providers_);
        bbt->schedule(**flow, nullptr);

        while (bbt->hasRunPoints())
        {
            bool progress = false;

            for (auto iterator = bbt->getRunPointBegin(); iterator != bbt->getRunPointEnd(); )
            {
                BBT::ExecutionResult const result = bbt->execute(*iterator);

                if (result == BBT::ExecutionResult::Completed)
                {
                    iterator = bbt->removeRunPoint(iterator);
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

                    continue;
                }

                if (result == BBT::ExecutionResult::Error)
                {
                    return std::nullopt;
                }
            }

            if (!progress && bbt->hasRunPoints())
            {
                bbt->reportBlockers();

                return std::nullopt;
            }
        }

        utility::Owned<Unit> unit = utility::makeOwned<Unit>();
        if (reporter_.isFailed())
            return std::nullopt;

        context_.print<Printer>(*unit, "cet", file);
        context_.graph<Grapher>(*unit, "cet", file);

        return unit;
    }

    utility::Optional<utility::Owned<bbt::UnorderedScope>> readUnorderedScope(std::filesystem::path const& file)
    {
        return segmenter_.segmentUnorderedFile(file);
    }

    void add(utility::Owned<Provider> provider)
    {
        providers_.emplace_back(std::move(provider));
    }

private:
    sources::SourceTree& source_tree_;
    core::Reporter& reporter_;
    utility::List<utility::Owned<Provider>> providers_ = {};
    bbt::Segmenter segmenter_;
    core::Context& context_;
};

ance::cet::Runner::Runner(sources::SourceTree& source_tree, core::Reporter& reporter, core::Context& context)
    : implementation_(utility::makeOwned<Implementation>(source_tree, reporter, context))
{}

ance::cet::Runner::~Runner() = default;

void ance::cet::Runner::add(utility::Owned<Provider> provider)
{
    implementation_->add(std::move(provider));
}

ance::utility::Optional<ance::utility::Owned<ance::cet::Unit>> ance::cet::Runner::runOrderedFile(std::filesystem::path const& file)
{
    return implementation_->runOrderedFile(file);
}
