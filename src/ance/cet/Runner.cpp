#include "Runner.h"

#include "Temporary.h"

#include <expected>
#include <filesystem>
#include <functional>
#include <list>
#include <string>
#include <vector>

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
        : source_tree_(source_tree)
        , reporter_(reporter)
        , read_unordered_scope_(std::move(get_unordered_scope))
        , global_scope_(utility::makeOwned<GlobalScope>(providers))
        {}
        
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

            if (!actual.isAssignableTo(expected))
            {
                reporter_.error("Expected type '" + expected.name() + "' but got '" + actual.name() + "'", location);
                ok = false;
            }

            return ok;
        }

        [[nodiscard]] bool requireSignature(core::Signature const& signature, utility::List<std::reference_wrapper<bbt::Temporary const>> const& arguments, core::Location const& location)
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
                Temporary& temporary = scope().getTemporary(argument.get());

                auto const& argument_value = temporary.getValue();
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

        [[nodiscard]] Scope& scope()
        {
            if (state_.current_scope != nullptr)
            {
                return *state_.current_scope;
            }

            return *global_scope_;
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
            utility::Shared<bbt::Value> condition = scope().getTemporary(branch_link.condition).getValue();

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
            utility::Shared<bbt::Value> target = scope().getTemporary(store.target).getValue();
            utility::Shared<bbt::Value> value = scope().getTemporary(store.value).getValue();

            if (!requireType(core::Type::VariableRef(), target->type(), store.target.location))
            {
                abort();
                return;
            }

            Variable& variable = target->as<VariableRefValue>().value();

            bool const is_defined = variable.isDefined();

            if (variable.isFinal() && is_defined)
            {
                reporter_.error("Cannot store to final variable '" + variable.name() + "'", store.target.location);
                abort();
                return;
            }

            core::Type const& type = variable.type();

            if (!requireType(type, value->type(), store.value.location))
            {
                abort();
                return;
            }

            variable.setValue(value);
        }

        void visit(bbt::Temporary const& temporary) override
        {
            scope().createTemporary(temporary);
        }

        void visit(bbt::CopyTemporary const& write_temporary) override
        {
            utility::Shared<bbt::Value> value = scope().getTemporary(write_temporary.source).getValue();
            scope().getTemporary(write_temporary.destination).setValue(value);
        }

        void visit(bbt::Intrinsic const& intrinsic) override
        {
            if (!requireSignature(intrinsic.intrinsic.signature(), intrinsic.arguments, intrinsic.location))
            {
                abort();
                return;
            }

            utility::List<utility::Shared<bbt::Value>> arguments = {};

            for (auto argument : intrinsic.arguments) { arguments.emplace_back(scope().getTemporary(argument.get()).getValue()); }

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
                scope().getTemporary(intrinsic.destination).setValue(result.getResult());
            }
        }

        void visit(bbt::Call const& call) override
        {
            RunPoint& run_point = *state_.current_run_point;

            if (run_point.return_value.hasValue())
            {
                scope().getTemporary(call.destination).setValue(run_point.return_value.value());
                run_point.return_value = std::nullopt;

                return;
            }

            utility::Shared<bbt::Value> called = scope().getTemporary(call.called).getValue();

            if (!requireType(core::Type::Function(), called->type(), call.called.location))
            {
                abort();
                return;
            }

            bbt::Function const& function = called->as<bbt::Function>();

            if (!requireSignature(function.signature(), call.arguments, call.location))
            {
                abort();
                return;
            }

            utility::List<utility::Shared<bbt::Value>> arguments = {};
            for (auto argument : call.arguments) { arguments.emplace_back(scope().getTemporary(argument.get()).getValue()); }

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

                (*variable)->as<VariableRefValue>().value().setValue(argument);
            }

            run_point.stack.emplace_back(function.body().entry, function_scope);

            yield();
        }

        void visit(bbt::Read const& read) override
        {
            utility::Shared<bbt::Value> target = scope().getTemporary(read.target).getValue();

            if (!requireType(core::Type::VariableRef(), target->type(), read.target.location))
            {
                abort();
                return;
            }

            Variable& variable = target->as<VariableRefValue>().value();

            bool const is_defined = variable.isDefined();
            if (!is_defined)
            {
                reporter_.error("Reading from undefined variable '" + variable.name() + "'", read.target.location);
                abort();
                return;
            }

            utility::Shared<bbt::Value> value = variable.getValue();
            scope().getTemporary(read.destination).setValue(value);
        }

        void visit(bbt::Constant const& constant) override
        {
            scope().getTemporary(constant.destination).setValue(constant.value->clone());
        }

        void visit(bbt::Default const& default_value) override
        {
            utility::Shared<bbt::Value> type_value = scope().getTemporary(default_value.type).getValue();

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
            scope().getTemporary(default_value.destination).setValue(value);
        }

        void visit(bbt::CurrentScope const& current_scope) override
        {
            scope().getTemporary(current_scope.destination).setValue(ScopeValue::make(scope()));
        }

        void visit(bbt::UnaryOperation const& unary_operation) override
        {
            utility::Shared<bbt::Value> value = scope().getTemporary(unary_operation.operand).getValue();

            if (!requireType(core::Type::Bool(), value->type(), unary_operation.operand.location))
            {
                abort();
                return;
            }

            switch (unary_operation.op)
            {
                case core::UnaryOperator::NOT:
                    scope().getTemporary(unary_operation.destination).setValue(bbt::BoolValue::make(!value->as<bbt::BoolValue>().value()));
                    break;
            }
        }

        void visit(bbt::TypeOf const& type_of) override
        {
            utility::Shared<bbt::Value> value = scope().getTemporary(type_of.expression).getValue();
            scope().getTemporary(type_of.destination).setValue(bbt::TypeValue::make(value->type()));
        }

        void visit(bbt::OrderedScopeEnter const&) override
        {
            state_.current_scope = scopes_.emplace_back(utility::makeOwned<OrderedScope>(this->scope())).get();

            // todo: associate the value storage with the scope so that context switch works better
        }

        void visit(bbt::OrderedScopeExit const&) override
        {
            state_.current_scope = scope().parent();

            // todo: destructors and stuff, clean up value storage
            // todo: maybe deleting the scope instance is a good idea?
        }

      private:
        sources::SourceTree& source_tree_;
        core::Reporter& reporter_;
        std::function<utility::Optional<utility::Owned<bbt::UnorderedScope>>(std::filesystem::path const&)> read_unordered_scope_;

        void scheduleUnorderedScope(bbt::UnorderedScope const& scope)
        {
            Scope* unordered_scope = scopes_.emplace_back(utility::makeOwned<UnorderedScope>(*global_scope_)).get();

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

        IntrinsicsRunner intrinsics_ {source_tree_, reporter_, include_};

        std::list<RunPoint> run_points_ = {};
        utility::List<utility::Owned<bbt::UnorderedScope>> roots_;
        std::vector<utility::Owned<Scope>> scopes_ = {};
        utility::Owned<GlobalScope> global_scope_;

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
