#include "Runner.h"

#include "Temporary.h"
#include "Variable.h"

#include <expected>
#include <filesystem>
#include <functional>
#include <list>
#include <string>
#include <utility>
#include <vector>

#include "ance/core/Intrinsic.h"

#include "ance/bbt/Function.h"
#include "ance/bbt/IntrinsicSignature.h"
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
            run_points_.emplace_back(flow.entry, scope != nullptr ? scope : global_scope_.get());
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

            return {result, bbt::Unit::make()};
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

        bool expectType(bbt::Type const& expected, utility::Shared<bbt::Value> value, core::Location const& location) const
        {
            // todo: as soon as l-refs are parameterized, this function needs to be updated to take the actual type instead of the value

            bool ok = true;

            utility::Shared<bbt::Type> actual = value->type();

            while (*actual == *bbt::Type::LRef())
            {
                auto const& reference = value->as<LReference>();
                Address const& address = reference.address();

                value = address.read();
                actual = value->type();
            }

            if (*actual != expected)
            {
                reporter_.error("Expected type '" + expected.name() + "' but got '" + actual->name() + "'", location);
                ok = false;
            }

            return ok;
        }

        static utility::Shared<bbt::Value> dereference(utility::Shared<bbt::Value> value)
        {
            utility::Shared<bbt::Type> actual = value->type();

            while (*actual == *bbt::Type::LRef())
            {
                auto const& reference = value->as<LReference>();
                Address const& address = reference.address();

                value = address.read();
                actual = value->type();
            }

            return value;
        }

        template <typename T>
        static T const& dereference(utility::Shared<bbt::Value> value)
        {
            return dereference(value)->as<T>();
        }

        [[nodiscard]] bool expectSignature(bbt::Signature const& signature,
                                           utility::List<std::reference_wrapper<bbt::Temporary const>> const& arguments,
                                           core::Location const& location)
        {
            // todo: as soon as l-refs are parameterized, this function needs to be updated to take the actual types instead of the temporaries

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

                auto const& type = *signature.parameters()[i].type;

                ok &= expectType(type, temporary.read(), argument.get().location);
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
            utility::Shared<bbt::Value> condition = scope().getTemporary(branch_link.condition).read();

            if (!expectType(*bbt::Type::Bool(), condition, branch_link.condition.location))
            {
                abort();
                return;
            }

            if (dereference<bbt::Bool>(condition).value())
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
            utility::Shared<bbt::Value> target = scope().getTemporary(store.target).read();
            utility::Shared<bbt::Value> value = scope().getTemporary(store.value).read();

            if (!expectType(*bbt::Type::VariableRef(), target, store.target.location))
            {
                abort();
                return;
            }

            Variable& variable = target->as<VariableRef>().value();

            bool const is_defined = variable.isDefined();

            if (variable.isFinal() && is_defined)
            {
                reporter_.error("Cannot store to final variable '" + variable.name() + "'", store.target.location);
                abort();
                return;
            }

            bbt::Type const& type = *variable.type();

            if (!expectType(type, value, store.value.location))
            {
                abort();
                return;
            }

            variable.write(dereference(value));
        }

        void visit(bbt::Temporary const& temporary) override
        {
            scope().createTemporary(temporary);
        }

        void visit(bbt::CopyTemporary const& write_temporary) override
        {
            utility::Shared<bbt::Value> value = scope().getTemporary(write_temporary.source).read();
            scope().getTemporary(write_temporary.destination).write(dereference(value));
        }

        void visit(bbt::Intrinsic const& intrinsic) override
        {
            auto [signature, _] = bbt::IntrinsicSignature::get(intrinsic.intrinsic);

            if (!expectSignature(signature, intrinsic.arguments, intrinsic.location))
            {
                abort();
                return;
            }

            utility::List<utility::Shared<bbt::Value>> arguments = {};

            for (auto argument : intrinsic.arguments)
            {
                utility::Shared<bbt::Value> value = scope().getTemporary(argument.get()).read();
                arguments.emplace_back(dereference(value));
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
                scope().getTemporary(intrinsic.destination).write(dereference(result.getResult()));
            }
        }

        void visit(bbt::Call const& call) override
        {
            RunPoint& run_point = *state_.current_run_point;

            if (run_point.return_value.hasValue())
            {
                scope().getTemporary(call.destination).write(run_point.return_value.value());
                run_point.return_value = std::nullopt;

                return;
            }

            utility::Shared<bbt::Value> called = scope().getTemporary(call.called).read();

            if (!expectType(*bbt::Type::Function(), called, call.called.location))
            {
                abort();
                return;
            }

            utility::Shared<bbt::Function> function = called.cast<bbt::Function>();
            bbt::Signature signature = function->signature();

            if (!expectSignature(signature, call.arguments, call.location))
            {
                abort();
                return;
            }

            utility::List<utility::Shared<bbt::Value>> arguments = {};
            for (auto argument : call.arguments) { arguments.emplace_back(scope().getTemporary(argument.get()).read()); }

            Scope& function_scope = global_scope_->addChildScope(utility::makeOwned<OrderedScope>(*global_scope_));

            for (size_t index = 0; index < signature.arity(); ++index)
            {
                bbt::Signature::Parameter& parameter = signature[index];
                utility::Shared<bbt::Value> argument = arguments[index];

                utility::Optional<utility::Shared<bbt::Value>> variable = function_scope.declare(parameter.name, parameter.type, true, core::Location::global(), reporter_);

                if (!variable.hasValue())
                {
                    abort();
                    return;
                }

                (*variable)->as<VariableRef>().value().write(dereference(argument));
            }

            run_point.stack.emplace_back(function->body().entry, &function_scope);

            yield();
        }

        void visit(bbt::Read const& read) override
        {
            utility::Shared<bbt::Value> target = scope().getTemporary(read.target).read();

            if (!expectType(*bbt::Type::VariableRef(), target, read.target.location))
            {
                abort();
                return;
            }

            Variable& variable = target->as<VariableRef>().value();

            bool const is_defined = variable.isDefined();
            if (!is_defined)
            {
                reporter_.error("Reading from undefined variable '" + variable.name() + "'", read.target.location);
                abort();
                return;
            }

            utility::Shared<bbt::Value> value = variable.read();
            scope().getTemporary(read.destination).write(value);
        }

        void visit(bbt::Constant const& constant) override
        {
            // Because the value class is immutable, this operation is logically const, but requires mutability to copy the shared ownership.
            bbt::Constant* mutable_constant = const_cast<bbt::Constant*>(&constant); // todo: think about a nicer way to do this

            scope().getTemporary(constant.destination).write( mutable_constant->value);
        }

        void visit(bbt::Default const& default_value) override
        {
            utility::Shared<bbt::Value> type_value = scope().getTemporary(default_value.type).read();

            if (!expectType(*bbt::Type::Self(), type_value, default_value.type.location))
            {
                abort();
                return;
            }

            auto get_default_value = [&](bbt::Type const& type) -> utility::Shared<bbt::Value> {
                // todo: should become default constructor call at some point

                if (type == *bbt::Type::Bool()) return bbt::Bool::make(false);
                if (type == *bbt::Type::Unit()) return bbt::Unit::make();
                if (type == *bbt::Type::Size()) return bbt::Size::make(0);
                if (type == *bbt::Type::Location()) return bbt::Location::make(core::Location::global());
                if (type == *bbt::Type::String()) return bbt::String::make("");

                reporter_.error("Cannot create default value for type '" + type.name() + "'", default_value.type.location);

                return bbt::Unit::make();
            };

            utility::Shared<bbt::Value> value = get_default_value(*type_value.cast<bbt::Type>());
            scope().getTemporary(default_value.destination).write(value);
        }

        void visit(bbt::CurrentScope const& current_scope) override
        {
            scope().getTemporary(current_scope.destination).write(ScopeRef::make(scope()));
        }

        void visit(bbt::UnaryOperation const& unary_operation) override
        {
            utility::Shared<bbt::Value> value = scope().getTemporary(unary_operation.operand).read();

            if (!expectType(*bbt::Type::Bool(), value, unary_operation.operand.location))
            {
                abort();
                return;
            }

            switch (unary_operation.op)
            {
                case core::UnaryOperator::NOT:
                    scope().getTemporary(unary_operation.destination).write(bbt::Bool::make(!value->as<bbt::Bool>().value()));
                    break;
            }
        }

        void visit(bbt::TypeOf const& type_of) override
        {
            utility::Shared<bbt::Value> value = scope().getTemporary(type_of.expression).read();
            scope().getTemporary(type_of.destination).write(value->type());
        }

        void visit(bbt::OrderedScopeEnter const&) override
        {
            state_.current_scope = &scope().addChildScope(utility::makeOwned<OrderedScope>(scope()));
        }

        void visit(bbt::OrderedScopeExit const&) override
        {
            Scope& child_scope = scope();

            state_.current_scope = child_scope.parent();
            state_.current_scope->removeChildScope(child_scope);

            // todo: destructors and stuff, clean up value storage
        }

      private:
        sources::SourceTree& source_tree_;
        core::Reporter& reporter_;
        std::function<utility::Optional<utility::Owned<bbt::UnorderedScope>>(std::filesystem::path const&)> read_unordered_scope_;

        void scheduleUnorderedScope(bbt::UnorderedScope const& scope)
        {
            Scope& unordered_scope = global_scope_->addChildScope(utility::makeOwned<UnorderedScope>(*global_scope_));

            for (auto const& flow : scope.flows)
            {
                schedule(*flow, &unordered_scope);
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
