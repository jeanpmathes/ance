#include "Runner.h"

#include "Temporary.h"
#include "Variable.h"

#include <expected>
#include <filesystem>
#include <functional>
#include <list>
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
            RunPoint(bbt::BasicBlock const& start, Scope* initial_scope) : block(&start), scope(initial_scope) {}

            bbt::BasicBlock const* block           = nullptr;
            size_t                 statement_index = 0;
            Scope*                 scope           = nullptr;

            utility::Optional<utility::Shared<bbt::Value>> return_value = std::nullopt;

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

            void popLevel(utility::Shared<bbt::Value> lower_return_value)
            {
                stack().pop_back();

                auto next = this;

                if (!stack().empty())
                {
                    next = &stack().back();
                }

                next->return_value = lower_return_value;
            }

            void pushLevel(bbt::BasicBlock const& start, Scope& initial_scope)
            {
                RunPoint& lower_level     = stack().emplace_back(start, &initial_scope);
                lower_level.target_stack_ = &stack_;
            }

            utility::Optional<PendingResolution> const& getBlocker() const
            {
                return getExecutableRunPoint().blocker_;
            }

            void clearBlocker()
            {
                blocker_ = std::nullopt;
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

            std::list<RunPoint>  stack_;
            std::list<RunPoint>* target_stack_ = &stack_;

            utility::Optional<PendingResolution> blocker_ = std::nullopt;
        };

        BBT(sources::SourceTree&                                                                       source_tree,
            core::Reporter&                                                                            reporter,
            bbt::TypeContext&                                                                          type_context,
            std::function<utility::Optional<utility::Owned<bbt::Flows>>(std::filesystem::path const&)> get_flows)
            : source_tree_(source_tree)
            , reporter_(reporter)
            , type_context_(type_context)
            , read_flows_(std::move(get_flows))
            , core_language_scope_(utility::makeOwned<CoreScope>(type_context))
            , project_scope_(core_language_scope_->addChildScope(utility::makeOwned<UnorderedScope>(*core_language_scope_, type_context)))
        {}

        ~BBT() override = default;

        void schedule(bbt::Flow const& flow, Scope* scope)
        {
            run_points_.emplace_back(flow.entry, scope != nullptr ? scope : &project_scope_);
        }

        void scheduleCore(utility::Owned<bbt::Flow> flow)
        {
            bbt::Flow& flow_ref = *flow;

            core_flows_.emplace_back(std::move(flow));

            schedule(flow_ref, core_language_scope_.get());
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
                auto const& blocker = run_point.getBlocker();

                if (blocker.hasValue())
                {
                    auto const& [identifier, reason] = blocker.value();

                    auto msg = reporter_.error(identifier.location());
                    msg << "Cannot resolve name " << identifier;

                    if (std::holds_alternative<FindResult::Erased>(reason))
                    {
                        auto const& [erase_location] = std::get<FindResult::Erased>(reason);
                        msg << core::Reporter::Annotation(erase_location) << identifier << " was erased here";
                    }
                }
            }
        }

        std::tuple<ExecutionResult, utility::Shared<bbt::Value>> execute(RunPoint* run_point)
        {
            State previous_state = std::move(state_);
            state_               = State(run_point->scope, run_point, run_point->statement_index, run_point->block);

            run_point->clearBlocker();

            reporter_.trace(prefix, core::Location::project())
                << "execute run point enter {block=" << (state_.next != nullptr ? std::to_string(state_.next->id) : "null")
                << ", statement_index=" << state_.current_statement_index << "}";

            while (!state_.execution_result.hasValue() && state_.next != nullptr)
            {
                run_point->block = state_.next;
                visit(*state_.next);
            }

            run_point->scope           = state_.current_scope;
            run_point->block           = state_.next;
            run_point->statement_index = state_.current_statement_index;

            ExecutionResult const       result       = state_.execution_result.valueOr(ExecutionResult::Completed);
            utility::Shared<bbt::Value> return_value = state_.return_value.valueOr(bbt::Unit::make(type_context_));

            reporter_.trace(prefix, core::Location::project()) << "execute run point exit {result=" << result << ", return_value=" << return_value->toString()
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

        [[nodiscard]] bool expectType(bbt::Type const& expected, bbt::Type const& actual, core::Location const& location) const
        {
            bool ok = true;

            bbt::Type const* actual_ptr = &actual;

            while (actual_ptr->isLReference())
            {
                actual_ptr = &actual_ptr->getConstructorType(0);
            }

            if (*actual_ptr != expected)
            {
                reporter_.error(location) << "Expected type " << expected.annotated() << " but got " << actual_ptr->annotated();
                ok = false;
            }

            return ok;
        }

        [[nodiscard]] bool expectSignature(bbt::Signature const&                                         signature,
                                           utility::List<std::reference_wrapper<bbt::Type const>> const& argument_types,
                                           utility::List<core::Location> const&                          argument_locations,
                                           core::Location const&                                         location)
        {
            bool ok = true;

            size_t const arity          = signature.arity();
            size_t const argument_count = argument_types.size();

            if (signature.isVariadic())
            {
                if (argument_count < arity)
                {
                    reporter_.error(location) << "Call to " << signature.annotated() << " with too few arguments: expected at least " << arity << " but got " << argument_count;
                    return false;
                }

                for (size_t index = 0; index < arity; index++)
                {
                    bbt::Type const&      parameter_type    = *signature.parameters()[index].type;
                    bbt::Type const&      argument_type     = argument_types[index].get();
                    core::Location const& argument_location = argument_locations[index];

                    ok &= expectType(parameter_type, argument_type, argument_location);
                }
            }
            else
            {
                if (arity != argument_count)
                {
                    reporter_.error(location) << "Call to " << signature.annotated() << " with wrong number of arguments: expected " << arity << " but got " << argument_count;
                    ok = false;
                }

                if (!ok) return false;

                for (size_t index = 0; index < argument_count; index++)
                {
                    bbt::Type const&      parameter_type    = *signature.parameters()[index].type;
                    bbt::Type const&      argument_type     = argument_types[index].get();
                    core::Location const& argument_location = argument_locations[index];

                    ok &= expectType(parameter_type, argument_type, argument_location);
                }
            }

            return ok;
        }

        [[nodiscard]] static utility::Shared<bbt::Value> deLReference(utility::Shared<bbt::Value> value)
        {
            while (value->type()->isLReference())
            {
                auto const&    reference = value->as<LReference>();
                Address const& address   = reference.address();

                value = address.read();
            }

            return value;
        }

        template<typename T>
        static T const& deLReference(utility::Shared<bbt::Value> value)
        {
            return deLReference(value)->as<T>();
        }

        struct TemporaryOutput
        {
            BBT*                  bbt;
            bbt::Temporary const& temporary;

            friend std::ostream& operator<<(std::ostream& os, TemporaryOutput const& self)
            {
                utility::Shared<bbt::Value> value = self.bbt->scope().getTemporary(self.temporary).read();
                return os << self.temporary.id() << "={value=" << value->toString() << ", type=" << value->type()->name() << "}";
            }
        };

        TemporaryOutput temp(bbt::Temporary const& temporary)
        {
            return TemporaryOutput {this, temporary};
        }

        core::Reporter::MessageBuilder trace(std::string_view const link_name, bbt::Link const& link)
        {
            auto msg = reporter_.trace(prefix, core::Location::project());
            msg << "visit link " << link_name << " " << link.location << " {block=" << (state_.next != nullptr ? std::to_string(state_.next->id) : "null")
                << "}";
            return msg;
        }

        core::Reporter::MessageBuilder trace(std::string_view const statement_name, bbt::Statement const& statement)
        {
            auto msg = reporter_.trace(prefix, core::Location::project());
            msg << "visit statement " << statement_name << " " << statement.location
                << " {block=" << (state_.next != nullptr ? std::to_string(state_.next->id) : "null") << ", statement_index=" << state_.current_statement_index
                << "}";
            return msg;
        }

        void abort()
        {
            reporter_.trace(prefix, core::Location::project()) << "abort execution";

            state_.execution_result = ExecutionResult::Error;

            state_.current_run_point->clearBlocker();
        }

        void block(PendingResolution const& blocker)
        {
            reporter_.trace(prefix, core::Location::project()) << "block execution pending on " << blocker.identifier;

            state_.execution_result = ExecutionResult::Pending;

            state_.current_run_point->setBlocker(blocker);
        }

        void yield()
        {
            reporter_.trace(prefix, core::Location::project()) << "yield";

            state_.execution_result = ExecutionResult::Yield;

            state_.current_run_point->clearBlocker();
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
            assert(false);// todo: that is why we need to change this before we use it

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
            trace("Return", return_link) << ", return_value=" << (state_.return_value.hasValue() ? state_.return_value.value()->toString() : "()");

            if (!state_.return_value.hasValue())
            {
                state_.return_value = bbt::Unit::make(type_context_);
            }

            state_.next = nullptr;
        }

        void visit(bbt::Branch const& branch_link) override
        {
            trace("Branch", branch_link) << ", true_branch=" << branch_link.true_branch.id << ", false_branch=" << branch_link.false_branch.id
                                         << ", condition=" << temp(branch_link.condition);

            utility::Shared<bbt::Value> condition = scope().getTemporary(branch_link.condition).read();

            if (!expectType(*type_context_.getBool(), *condition->type(), branch_link.condition.location))
            {
                abort();
                return;
            }

            if (deLReference<bbt::Bool>(condition).value())
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

        void visit(bbt::Store const& store) override
        {
            trace("Store", store) << ", target=" << temp(store.target) << ", value=" << temp(store.value);

            utility::Shared<bbt::Value> target = scope().getTemporary(store.target).read();
            utility::Shared<bbt::Value> value  = scope().getTemporary(store.value).read();

            if (!target->type()->isLReference())
            {
                reporter_.error(store.target.location) << "Cannot store to non-l-value";
                abort();
                return;
            }

            // todo: this is not ideal with final variables, technically we could get an l-ref to it when it is not defined yet but then write twice to it through the same l-ref

            utility::Shared<LReference> reference = target.cast<LReference>();

            if (!expectType(*target->type()->getConstructorType(0), *value->type(), store.value.location))
            {
                abort();
                return;
            }

            reference->address().write(deLReference(value));
        }

        void visit(bbt::Access const& access) override
        {
            trace("Access", access) << ", variable=" << access.variable.id() << ", destination=" << access.destination.id();

            utility::Shared<bbt::Value> target = scope().getTemporary(access.variable).read();

            if (!expectType(*type_context_.getVariableRef(), *target->type(), access.variable.location))
            {
                abort();
                return;
            }

            Variable& variable = target->as<VariableRef>().value();

            // todo: using type inference, we could determine whether we want to later write to it or if not, if yes and final we could output an error here
            // todo: we could also check whether it is already defined if we want to read later, catching reads from undefined variables

            // todo: right now, reading from this lref would be possible even if the variable is not defined

            scope().getTemporary(access.destination).write(variable.access());
        }

        void visit(bbt::Temporary const& temporary) override
        {
            trace("Temporary", temporary) << ", id=" << temporary.id();

            scope().createTemporary(temporary);
        }

        void visit(bbt::CopyTemporary const& copy_temporary) override
        {
            trace("CopyTemporary", copy_temporary) << ", source=" << temp(copy_temporary.source) << ", destination=" << copy_temporary.destination.id();

            utility::Shared<bbt::Value> value = scope().getTemporary(copy_temporary.source).read();
            scope().getTemporary(copy_temporary.destination).write(deLReference(value));
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

            auto [signature, _] = bbt::getIntrinsicSignature(intrinsic.intrinsic, type_context_);

            utility::List<std::reference_wrapper<bbt::Type const>> argument_types     = {};
            utility::List<core::Location>                          argument_locations = {};

            for (auto argument : intrinsic.arguments)
            {
                utility::Shared<bbt::Value> value = scope().getTemporary(argument.get()).read();
                argument_types.emplace_back(*value->type());
                argument_locations.emplace_back(argument.get().location);
            }

            if (!expectSignature(signature, argument_types, argument_locations, intrinsic.location))
            {
                abort();
                return;
            }

            utility::List<utility::Shared<bbt::Value>> arguments = {};

            for (auto argument : intrinsic.arguments)
            {
                utility::Shared<bbt::Value> value = scope().getTemporary(argument.get()).read();
                arguments.emplace_back(deLReference(value));
            }

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
                scope().getTemporary(intrinsic.destination).write(deLReference(result.getResult()));
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
                scope().getTemporary(call.destination).write(deLReference(run_point.return_value.value()));

                run_point.return_value = std::nullopt;

                return;
            }

            utility::Shared<bbt::Value> called = scope().getTemporary(call.called).read();

            if (!expectType(*type_context_.getFunction(), *called->type(), call.called.location))
            {
                abort();
                return;
            }

            utility::Shared<bbt::Function> function  = called.cast<bbt::Function>();
            bbt::Signature                 signature = function->signature();

            utility::List<std::reference_wrapper<bbt::Type const>> argument_types     = {};
            utility::List<core::Location>                          argument_locations = {};

            for (auto argument : call.arguments)
            {
                utility::Shared<bbt::Value> value = scope().getTemporary(argument.get()).read();
                argument_types.emplace_back(*value->type());
                argument_locations.emplace_back(argument.get().location);
            }

            if (!expectSignature(signature, argument_types, argument_locations, call.location))
            {
                abort();
                return;
            }

            utility::List<utility::Shared<bbt::Value>> arguments = {};
            for (auto argument : call.arguments)
            {
                arguments.emplace_back(scope().getTemporary(argument.get()).read());
            }

            Scope& function_scope = project_scope_.addChildScope(utility::makeOwned<OrderedScope>(project_scope_, type_context_));

            for (size_t index = 0; index < signature.arity(); index++)
            {
                bbt::Signature::Parameter&  parameter = signature[index];
                utility::Shared<bbt::Value> argument  = arguments[index];

                utility::Optional<utility::Shared<bbt::Value>> variable =
                    function_scope.declare(parameter.name, parameter.type, true, core::Location::project(), reporter_);

                if (!variable.hasValue())
                {
                    abort();
                    return;
                }

                (*variable)->as<VariableRef>().value().write(deLReference(argument));
            }

            run_point.pushLevel(function->body().entry, function_scope);

            yield();
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

                msg << "}" << ", return_type=" << temp(function_constructor.return_type) << ", destination=" << function_constructor.destination.id();
            }

            utility::List<bbt::Signature::Parameter> parameters = {};
            for (auto const& param : function_constructor.parameters)
            {
                utility::Shared<bbt::Value> type_value = scope().getTemporary(param.type).read();
                if (!expectType(*type_context_.getType(), *type_value->type(), param.type.location))
                {
                    abort();
                    return;
                }
                parameters.emplace_back(param.identifier, type_value.cast<bbt::Type>());
            }

            bbt::Signature const signature = bbt::Signature(function_constructor.name, std::move(parameters));

            utility::Shared<bbt::Value> return_type = scope().getTemporary(function_constructor.return_type).read();
            if (!expectType(*type_context_.getType(), *return_type->type(), function_constructor.return_type.location))
            {
                abort();
                return;
            }

            utility::Shared<bbt::Function> function =
                utility::makeShared<bbt::Function>(signature, return_type.cast<bbt::Type>(), *function_constructor.body, type_context_);

            scope().getTemporary(function_constructor.destination).write(function);
        }

        void visit(bbt::Constant const& constant) override
        {
            trace("Constant", constant) << ", value=" << constant.value->toString() << ", type=" << constant.value->type().name() << ", destination=" << constant.destination.id();

            // Because the value class is immutable, this operation is logically const, but requires mutability to copy the shared ownership.
            auto* mutable_constant = const_cast<bbt::Constant*>(&constant);// todo: think about a nicer way to do this

            scope().getTemporary(constant.destination).write(mutable_constant->value);
        }

        void visit(bbt::Default const& default_value) override
        {
            trace("Default", default_value) << ", type=" << temp(default_value.type) << ", destination=" << default_value.destination.id();

            utility::Shared<bbt::Value> type_value = scope().getTemporary(default_value.type).read();

            if (!expectType(*type_context_.getType(), *type_value->type(), default_value.type.location))
            {
                abort();
                return;
            }

            auto get_default_value = [&](bbt::Type const& type) -> utility::Shared<bbt::Value> {
                // todo: should become default constructor call at some point

                if (type == *type_context_.getBool()) return bbt::Bool::make(false, type_context_);
                if (type == *type_context_.getUnit()) return bbt::Unit::make(type_context_);
                if (type == *type_context_.getSize()) return bbt::Size::make(0, type_context_);
                if (type == *type_context_.getLocation()) return bbt::Location::make(core::Location::project(), type_context_);
                if (type == *type_context_.getString()) return bbt::String::make("", type_context_);

                reporter_.error(default_value.type.location) << "Cannot create default value for type " << type.annotated();

                return bbt::Unit::make(type_context_);
            };

            utility::Shared<bbt::Value> value = get_default_value(*type_value.cast<bbt::Type>());
            scope().getTemporary(default_value.destination).write(value);
        }

        void visit(bbt::CurrentScope const& current_scope) override
        {
            trace("CurrentScope", current_scope) << ", destination=" << current_scope.destination.id();

            scope().getTemporary(current_scope.destination).write(ScopeRef::make(scope(), type_context_));
        }

        void visit(bbt::UnaryOperation const& unary_operation) override
        {
            trace("UnaryOperation", unary_operation) << ", op=" << unary_operation.op << ", operand=" << temp(unary_operation.operand) << ", destination=" << unary_operation.destination.id();

            utility::Shared<bbt::Value> value = scope().getTemporary(unary_operation.operand).read();

            if (!expectType(*type_context_.getBool(), *value->type(), unary_operation.operand.location))
            {
                abort();
                return;
            }

            switch (unary_operation.op)
            {
                case core::UnaryOperator::UNSPECIFIED:
                    abort();
                    break;

                case core::UnaryOperator::NOT:
                    scope().getTemporary(unary_operation.destination).write(bbt::Bool::make(!deLReference<bbt::Bool>(value).value(), type_context_));
                    break;
            }
        }

        void visit(bbt::TypeOf const& type_of) override
        {
            trace("TypeOf", type_of) << ", expression=" << temp(type_of.expression) << ", destination=" << type_of.destination.id();

            utility::Shared<bbt::Value> value = scope().getTemporary(type_of.expression).read();
            scope().getTemporary(type_of.destination).write(value->type());
        }

        void visit(bbt::OrderedScopeEnter const& scope_enter) override
        {
            trace("OrderedScopeEnter", scope_enter);

            state_.current_scope = &scope().addChildScope(utility::makeOwned<OrderedScope>(scope(), type_context_));
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
            trace("SetReturnValue", set_return_value) << ", value=" << temp(set_return_value.value);

            assert(!state_.return_value.hasValue());

            state_.return_value = deLReference(scope().getTemporary(set_return_value.value).read());
        }

        void declareCoreVariable(core::Identifier const& name, utility::Shared<bbt::Value> value)
        {
            value = deLReference(std::move(value));

            utility::Optional<utility::Shared<bbt::Value>> declared = core_language_scope_->declare(name, value->type(), true, core::Location::core(), reporter_);

            if (declared.hasValue())
                (*declared)->as<VariableRef>().value().write(std::move(value));
        }

      private:
        sources::SourceTree&                                                                       source_tree_;
        core::Reporter&                                                                            reporter_;
        bbt::TypeContext&                                                                          type_context_;
        std::function<utility::Optional<utility::Owned<bbt::Flows>>(std::filesystem::path const&)> read_flows_;

        void scheduleFlows(bbt::Flows const& flows)
        {
            for (auto const& flow : flows.flows)
            {
                schedule(*flow, &project_scope_);
            }
        }

        void scheduleUnorderedScope(bbt::UnorderedScope const& scope, Scope& parent_scope)
        {
            Scope& unordered_scope = parent_scope.addChildScope(utility::makeOwned<UnorderedScope>(parent_scope, type_context_));

            for (auto const& flow : scope.flows)
            {
                schedule(*flow, &unordered_scope);
            }
        }

        std::function<void(std::filesystem::path const&)> include_ = [this](std::filesystem::path const& path) {
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
        utility::List<utility::Owned<bbt::Flow>> core_flows_     = {};
        utility::List<utility::Owned<bbt::Flows>> included_flows_ = {};

        utility::Owned<CoreScope> core_language_scope_;
        Scope&                      project_scope_;

        struct State
        {
            RunPoint* current_run_point       = nullptr;
            size_t    current_statement_index = 0;
            Scope*    current_scope           = nullptr;

            bbt::BasicBlock const* next = nullptr;

            utility::Optional<utility::Shared<bbt::Value>> return_value     = std::nullopt;
            utility::Optional<ExecutionResult>             execution_result = std::nullopt;

            State() = default;

            State(Scope* scope, RunPoint* run_point, size_t const statement_index, bbt::BasicBlock const* next_block)
                : current_run_point(run_point)
                , current_statement_index(statement_index)
                , current_scope(scope)
                , next(next_block)
            {}
        };

        State state_;
    };

    explicit Implementation(sources::SourceTree& source_tree, core::Reporter& reporter, core::Context& context)
        : source_tree_(source_tree)
        , reporter_(reporter)
        , segmenter_(source_tree, reporter, context, type_context_)
        , context_(context)
        , bbt_(utility::makeOwned<BBT>(source_tree_, reporter_, type_context_, [&](std::filesystem::path const& f) { return readUnorderedFile(f); }))
    {}

    bool run(BBT& bbt)
    {
        while (bbt.hasRunPoints())
        {
            bool progress = false;

            for (auto iterator = bbt.getRunPointBegin(); iterator != bbt.getRunPointEnd();)
            {
                BBT::RunPoint&             run_point = *iterator;
                BBT::ExecutionResult const result    = bbt.execute(run_point);

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
                    return false;
                }
            }

            if (!progress && bbt.hasRunPoints())
            {
                bbt.reportBlockers();

                return false;
            }
        }

        return true;
    }

    utility::Optional<utility::Owned<Unit>> runProjectFile(std::filesystem::path const& file)
    {
        utility::Optional<utility::Owned<bbt::Flow>> flow = segmenter_.segmentOrderedFile(file);
        if (!flow.hasValue()) return std::nullopt;

        bbt_->schedule(**flow, nullptr);

        bool const ok = run(*bbt_);

        if (!ok) return std::nullopt;

        utility::Owned<Unit> unit = utility::makeOwned<Unit>();

        context_.print<Printer>(*unit, "cet", file);
        context_.graph<Grapher>(*unit, "cet", file);

        if (reporter_.isFailed()) return std::nullopt;

        return unit;
    }

    utility::Optional<utility::Owned<bbt::Flows>> readUnorderedFile(std::filesystem::path const& file)
    {
        return segmenter_.segmentUnorderedFile(file);
    }

    void declareCoreVariable(core::Identifier const& name, utility::Shared<bbt::Value> value)
    {
        bbt_->declareCoreVariable(name, value);
    }

    void declareCore(std::string const& code, std::string const& id)
    {
        utility::Optional<utility::Owned<bbt::Flow>> flow = segmenter_.segmentDeclaration(code, id);

        if (!flow.hasValue())
            throw std::logic_error("Failed to parse core code");

        bbt_->scheduleCore(std::move(flow.value()));

        bool const ok = run(*bbt_);

        if (!ok)
            throw std::logic_error("Failed to run core code");
    }

    bbt::TypeContext& getTypeContext()
    {
        return type_context_;
    }

  private:
    sources::SourceTree&                    source_tree_;
    core::Reporter&                         reporter_;
    bbt::TypeContext                        type_context_ {};
    bbt::Segmenter                          segmenter_;
    core::Context&                          context_;

    utility::Owned<BBT> bbt_;
};

ance::cet::Runner::Runner(sources::SourceTree& source_tree, core::Reporter& reporter, core::Context& context)
    : implementation_(utility::makeOwned<Implementation>(source_tree, reporter, context))
{}

ance::cet::Runner::~Runner() = default;

void ance::cet::Runner::declareCoreVariable(core::Identifier const& name, utility::Shared<bbt::Value> value)
{
    return implementation_->declareCoreVariable(name, std::move(value));
}

void ance::cet::Runner::declareCore(std::string const& code, std::string const& id)
{
    return implementation_->declareCore(code, id);
}

ance::utility::Optional<ance::utility::Owned<ance::cet::Unit>> ance::cet::Runner::runProjectFile(std::filesystem::path const& file)
{
    return implementation_->runProjectFile(file);
}

ance::bbt::TypeContext& ance::cet::Runner::types()
{
    return implementation_->getTypeContext();
}
