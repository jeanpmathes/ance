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
#include "ance/core/Value.h"

#include "ance/bbt/Function.h"
#include "ance/bbt/Node.h"
#include "ance/bbt/Segmenter.h"
#include "ance/cet/Node.h"
#include "ance/cet/Provider.h"

#include "Grapher.h"
#include "Printer.h"
#include "ance/sources/SourceTree.h"

struct ance::cet::Runner::Implementation
{
    class Variable
    {
    public:
        Variable(core::Identifier const& identifier, core::Type const& type, bool is_final, core::Location const& location)
            : identifier_(identifier), type_(type), variable_(identifier, type, is_final, location)
        {
        }

        [[nodiscard]] core::Identifier const& identifier() const { return identifier_; }
        [[nodiscard]] core::Type const& type() const { return type_; }
        [[nodiscard]] core::Variable const& variable() const { return variable_; }

    private:
        core::Identifier identifier_;
        core::Type const& type_;
        core::Variable variable_;
    };

    class Scope
    {
      protected:
        explicit Scope(Scope* parent) : parent_(parent)
        {
        }

      public:
        virtual ~Scope() = default;

        [[nodiscard]] Scope* parent() const { return parent_; }

        [[nodiscard]] utility::Optional<utility::Shared<core::Value>> declare(core::Identifier const& identifier, core::Type const& type, bool is_final, core::Location const& location, core::Reporter& reporter)
        {
            if (!canDeclare(identifier))
            {
                reporter.error("Declaring '" + identifier + "' in this scope would block previous access to outside of the scope", location);
                return std::nullopt;
            }

            utility::Owned<Variable> variable = utility::makeOwned<Variable>(identifier, type, is_final, location);
            Variable const& variable_ref = *variable;

            onDeclare(std::move(variable));

            return core::Value::makeEntityRef(variable_ref.variable());
        }

        [[nodiscard]] utility::Optional<utility::Shared<core::Value>> find(core::Identifier const& identifier,
                                                                           std::function<utility::Optional<utility::Shared<core::Value>>(core::Identifier const&)> const& provider)
        {
            Variable const* variable = onFind(identifier);

            if (variable != nullptr)
            {
                return core::Value::makeEntityRef(variable->variable());
            }

            if (parent_ != nullptr)
            {
                return parent_->find(identifier, provider);
            }

            return provider(identifier);
        }

      protected:
        [[nodiscard]] virtual bool                                                         canDeclare(core::Identifier const& identifier) const = 0;
        virtual void                                                                       onDeclare(utility::Owned<Variable> variable)   = 0;
        [[nodiscard]] virtual Variable const* onFind(core::Identifier const& identifier)  = 0;

      private:
        Scope* parent_;
    };

    class OrderedScope final : public Scope
    {
      public:
        explicit OrderedScope(Scope* parent)
            : Scope(parent)
        {}

        ~OrderedScope() override = default;

      protected:
        [[nodiscard]] bool canDeclare(core::Identifier const& identifier) const override
        {
            return !outer_identifiers_.contains(identifier);
        }

        void onDeclare(utility::Owned<Variable> variable) override
        {
            active_variables_.emplace(variable->identifier(), std::cref(*variable));
            all_variables_.emplace_back(std::move(variable));
        }

        [[nodiscard]] Variable const* onFind(core::Identifier const& identifier) override
        {
            if (active_variables_.contains(identifier))
            {
                return &active_variables_.at(identifier).get();
            }

            outer_identifiers_.insert(identifier);

            return nullptr;
        }

      private:
        std::vector<utility::Owned<Variable>> all_variables_ = {};
        std::map<core::Identifier, std::reference_wrapper<Variable const>> active_variables_ = {};
        std::set<core::Identifier> outer_identifiers_ = {};
    };

    class UnorderedScope final : public Scope
    {
      public:
        explicit UnorderedScope(Scope* parent)
            : Scope(parent)
        {}

        ~UnorderedScope() override = default;

      protected:
        [[nodiscard]] bool canDeclare(core::Identifier const& identifier) const override
        {
            return !variables_.contains(identifier);
        }

        void onDeclare(utility::Owned<Variable> variable) override
        {
            variables_.emplace(variable->identifier(), std::cref(*variable));
            all_variables_.emplace_back(std::move(variable));
        }

        [[nodiscard]] Variable const* onFind(core::Identifier const& identifier) override
        {
            if (variables_.contains(identifier))
            {
                return &variables_.at(identifier).get();
            }

            return nullptr;
        }

      private:
        std::vector<utility::Owned<Variable>> all_variables_ = {};
        std::map<core::Identifier, std::reference_wrapper<Variable const>> variables_ = {};
    };

    struct PendingResolution
    {
        core::Identifier identifier;
    };

    class Intrinsics final : core::IntrinsicVisitor
    {
    public:
        using IntrinsicVisitor::visit;

        Intrinsics(
            sources::SourceTree& source_tree,
            core::Reporter& reporter,
            std::function<utility::Optional<utility::Shared<core::Value>>(core::Identifier const&)> provide,
            std::function<void(std::filesystem::path const&)> include)
            : source_tree_(source_tree), reporter_(reporter), provide_(std::move(provide)), include_(std::move(include))
        {
        }

        utility::Optional<utility::Shared<core::Value>> run(core::Intrinsic const& intrinsic, utility::List<utility::Shared<core::Value>> const& arguments, core::Location const& location)
        {
            location_ = location;
            arguments_ = &arguments;
            return_value_ = core::Value::makeUnit();
            expected_return_type_ = &intrinsic.returnType();
            pending_resolution_ = std::nullopt;

            this->visit(intrinsic);

            location_ = core::Location::global();
            arguments_ = nullptr;
            expected_return_type_ = nullptr;

            return return_value_;
        }

        [[nodiscard]] bool isPending() const
        {
            return pending_resolution_.hasValue();
        }

        [[nodiscard]] PendingResolution const& pending() const
        {
            assert(pending_resolution_.hasValue());
            return pending_resolution_.value();
        }

        void visit(core::Dynamic const& dynamic) override
        {
            reporter_.error("Unsupported intrinsic '" + dynamic.identifier() + "'", location_);
        }

        void visit(core::NoOp const&) override
        {
            // Do nothing.
        }

        void visit(core::Declare const&) override
        {
            assert(arguments_->size() == 4);
            assert(arguments_->at(0)->type() == core::Type::Scope());
            assert(arguments_->at(1)->type() == core::Type::Ident());
            assert(arguments_->at(2)->type() == core::Type::Bool());
            assert(arguments_->at(3)->type() == core::Type::Self());

            Scope& scope = *static_cast<Scope*>(arguments_->at(0)->getScope());
            core::Identifier const& identifier = arguments_->at(1)->getIdentifier();
            bool const is_final = arguments_->at(2)->getBool();
            core::Type const& type = arguments_->at(3)->getType();

            auto variable = scope.declare(identifier, type, is_final, location_, reporter_);

            if (variable.hasValue())
            {
                setResult(std::move(*variable));
            }
            else
            {
                abort();
            }
        }

        void visit(core::Resolve const&) override
        {
            assert(arguments_->size() == 2);
            assert(arguments_->at(0)->type() == core::Type::Scope());
            assert(arguments_->at(1)->type() == core::Type::Ident());

            Scope& scope = *static_cast<Scope*>(arguments_->at(0)->getScope());
            core::Identifier const& identifier = arguments_->at(1)->getIdentifier();

            utility::Optional<utility::Shared<core::Value>> variable = scope.find(identifier, provide_);

            if (variable.hasValue())
            {
                setResult(std::move(*variable));
            }
            else
            {
                setPending(identifier);
            }
        }

        void visit(core::GetParent const&) override
        {
            assert(arguments_->size() == 1);
            assert(arguments_->at(0)->type() == core::Type::Scope());

            auto* scope = static_cast<Scope*>(arguments_->at(0)->getScope());

            if (scope->parent() == nullptr)
            {
                reporter_.error("Scope has no parent", location_);
                abort();
                return;
            }

            setResult(core::Value::makeScope(scope->parent()));
        }

        void visit(core::Log const&) override
        {
            assert(arguments_->size() == 2);
            assert(arguments_->at(0)->type() == core::Type::String());
            assert(arguments_->at(1)->type() == core::Type::Location());

            std::string const& value = arguments_->at(0)->getString();
            core::Location const& loc = arguments_->at(1)->getLocation();

            reporter_.info(value, loc);

            setResult(core::Value::makeUnit());
        }

        void visit(core::B2Str const&) override
        {
            assert(arguments_->size() == 1);
            assert(arguments_->at(0)->type() == core::Type::Bool());

            bool const value = arguments_->at(0)->getBool();

            setResult(core::Value::makeString(value ? "true" : "false"));
        }

        void visit(core::Include const&) override
        {
            assert(arguments_->size() == 2);
            assert(arguments_->at(0)->type() == core::Type::String());
            assert(arguments_->at(1)->type() == core::Type::Location());

            std::string const& file = arguments_->at(0)->getString();
            core::Location const& location = arguments_->at(1)->getLocation();

            std::filesystem::path const path = source_tree_.getFile(location.fileIndex()).getDirectory() / file;

            include_(path);
        }

    private:
        void setResult(utility::Shared<core::Value> value)
        {
            assert(value->type() == *expected_return_type_);

            return_value_ = std::move(value);
        }

        void abort()
        {
            pending_resolution_ = std::nullopt;
            return_value_ = std::nullopt;
        }

        void setPending(core::Identifier const& identifier)
        {
            pending_resolution_ = PendingResolution {identifier};
            return_value_ = std::nullopt;
        }

        sources::SourceTree& source_tree_;
        core::Reporter& reporter_;

        std::function<utility::Optional<utility::Shared<core::Value>>(core::Identifier const&)> provide_;
        std::function<void(std::filesystem::path const&)> include_;

        core::Location location_ = core::Location::global();
        utility::List<utility::Shared<core::Value>> const* arguments_ = nullptr;

        utility::Optional<utility::Shared<core::Value>> return_value_ = std::nullopt;
        core::Type const* expected_return_type_ = nullptr;
        utility::Optional<PendingResolution> pending_resolution_ = std::nullopt;
    };

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
            utility::Optional<utility::Shared<core::Value>> return_value = std::nullopt;
        };

        BBT(
            sources::SourceTree& source_tree,
            core::Reporter& reporter,
            std::function<utility::Optional<utility::Owned<bbt::UnorderedScope>>(std::filesystem::path const&)> get_unordered_scope,
            utility::List<utility::Owned<Provider>>& providers)
        : source_tree_(source_tree), reporter_(reporter), read_unordered_scope_(std::move(get_unordered_scope)), providers_(providers) {}
        ~BBT() override = default;

        void schedule(bbt::Flow const& flow)
        {
            run_points_.emplace_back(flow.entry, current_scope_);
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

        std::tuple<ExecutionResult, utility::Shared<core::Value>> execute(RunPoint* run_point)
        {
            RunPoint* previous_run_point = current_run_point_;
            bbt::BasicBlock const* previous_next = next_;
            size_t const previous_statement_index = current_statement_index_;
            Scope* previous_scope = current_scope_;
            utility::Optional<ExecutionResult> const previous_result = execution_result_;

            current_run_point_ = run_point;
            run_point->clearBlocker();

            execution_result_ = std::nullopt;
            next_ = run_point->block;
            current_statement_index_ = run_point->statement_index;
            current_scope_ = run_point->scope;

            while (!execution_result_.hasValue() && next_ != nullptr)
            {
                run_point->block = next_;
                visit(*next_);
            }

            run_point->scope = current_scope_;
            run_point->block = next_;
            run_point->statement_index = current_statement_index_;

            ExecutionResult const result = execution_result_.valueOr(ExecutionResult::Completed);

            current_scope_ = previous_scope;
            current_statement_index_ = previous_statement_index;
            next_ = previous_next;
            execution_result_ = previous_result;
            current_run_point_ = previous_run_point;

            return {result, core::Value::makeUnit()};
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
            execution_result_ = ExecutionResult::Error;

            current_run_point_->clearBlocker();
        }

        void block(PendingResolution const& blocker)
        {
            execution_result_ = ExecutionResult::Pending;

            current_run_point_->blocker = blocker;
        }

        void yield()
        {
            execution_result_ = ExecutionResult::Yield;

            current_run_point_->clearBlocker();
        }

        [[nodiscard]] Scope* scope()
        {
            return current_scope_;
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
            assert(current_run_point_ != nullptr);

            current_run_point_->block = &basic_block;
            current_run_point_->scope = current_scope_;

            size_t const statement_count = basic_block.statements.size();

            while (current_statement_index_ < statement_count)
            {
                current_run_point_->statement_index = current_statement_index_;
                current_run_point_->scope = current_scope_;

                visit(*basic_block.statements[current_statement_index_]);

                if (execution_result_.hasValue())
                {
                    return;
                }

                current_statement_index_ += 1;
            }

            current_run_point_->statement_index = current_statement_index_;
            current_run_point_->scope = current_scope_;

            current_statement_index_ = 0;
            visit(*basic_block.link);
        }

        void visit(bbt::ErrorLink const& error_link) override
        {
            reporter_.error("Cannot execute this link", error_link.location);

            abort();
        }

        void visit(bbt::Return const&) override
        {
            next_ = nullptr;
        }

        void visit(bbt::Branch const& branch_link) override
        {
            utility::Shared<core::Value> condition = temporaries_.at(&branch_link.condition);

            if (!requireType(core::Type::Bool(), condition->type(), branch_link.condition.location))
            {
                abort();
                return;
            }

            if (condition->getBool())
            {
                next_ = &branch_link.true_branch;
            }
            else
            {
                next_ = &branch_link.false_branch;
            }
        }

        void visit(bbt::Jump const& jump_link) override
        {
            next_ = &jump_link.target;
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
            utility::Shared<core::Value> target = temporaries_.at(&store.target);
            utility::Shared<core::Value> value = temporaries_.at(&store.value);

            if (!requireType(core::Type::EntityRef(), target->type(), store.target.location))
            {
                abort();
                return;
            }

            core::Entity const& entity = target->getEntity();

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
            utility::Shared<core::Value> value = core::Value::makeUnit();
            temporaries_.insert_or_assign(&temporary, value);
        }

        void visit(bbt::CopyTemporary const& write_temporary) override
        {
            utility::Shared<core::Value> value = temporaries_.at(&write_temporary.source);
            temporaries_.insert_or_assign(&write_temporary.destination, value);
        }

        void visit(bbt::Intrinsic const& intrinsic) override
        {
            if (!requireSignature(intrinsic.intrinsic.signature(), intrinsic.arguments, intrinsic.location))
            {
                abort();
                return;
            }

            utility::List<utility::Shared<core::Value>> arguments = {};
            for (auto argument : intrinsic.arguments) { arguments.emplace_back(temporaries_.at(&argument.get())); }

            auto result = intrinsics_.run(intrinsic.intrinsic, arguments, intrinsic.location);

            if (!result.hasValue())
            {
                if (intrinsics_.isPending())
                {
                    block(intrinsics_.pending());
                }
                else
                {
                    abort();
                }
                return;
            }

            temporaries_.insert_or_assign(&intrinsic.destination, result.value());
        }

        void visit(bbt::Call const& call) override
        {
            RunPoint& run_point = *current_run_point_;

            if (run_point.return_value.hasValue())
            {
                temporaries_.insert_or_assign(&call.destination, run_point.return_value.value());
                run_point.return_value = std::nullopt;

                return;
            }

            utility::Shared<core::Value> called = temporaries_.at(&call.called);

            if (!requireType(core::Type::EntityRef(), called->type(), call.called.location))
            {
                abort();
                return;
            }

            core::Entity const& entity = called->getEntity();

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

            utility::List<utility::Shared<core::Value>> arguments = {};
            for (auto argument : call.arguments) { arguments.emplace_back(temporaries_.at(&argument.get())); }

            Scope* function_scope = scopes_.emplace_back(utility::makeOwned<OrderedScope>(this->scope())).get();

            for (size_t i = 0; i < function.signature().arity(); ++i)
            {
                core::Signature::Parameter const& parameter = function.signature().parameters()[i];
                utility::Shared<core::Value>& argument = arguments[i];

                utility::Optional<utility::Shared<core::Value>> variable = function_scope->declare(parameter.name, parameter.type, true, core::Location::global(), reporter_);

                if (!variable.hasValue())
                {
                    abort();
                    return;
                }

                variables_.insert_or_assign(&(*variable)->getEntity(), argument);
            }

            run_point.stack.emplace_back(function.body().entry, function_scope);

            yield();
        }

        void visit(bbt::Read const& read) override
        {
            utility::Shared<core::Value> target = temporaries_.at(&read.target);

            if (!requireType(core::Type::EntityRef(), target->type(), read.target.location))
            {
                abort();
                return;
            }

            core::Entity const& entity = target->getEntity();

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

            utility::Shared<core::Value> value = variables_.at(&entity);
            temporaries_.insert_or_assign(&read.destination, value);
        }

        void visit(bbt::Constant const& constant) override
        {
            temporaries_.insert_or_assign(&constant.destination, constant.value->clone());
        }

        void visit(bbt::Default const& default_value) override
        {
            utility::Shared<core::Value> type_value = temporaries_.at(&default_value.type);

            if (!requireType(core::Type::Self(), type_value->type(), default_value.type.location))
            {
                abort();
                return;
            }

            utility::Shared<core::Value> value = core::Value::makeDefault(type_value->getType());
            temporaries_.insert_or_assign(&default_value.destination, value);
        }

        void visit(bbt::CurrentScope const& current_scope) override
        {
            temporaries_.insert_or_assign(&current_scope.destination, core::Value::makeScope(this->scope()));
        }

        void visit(bbt::UnaryOperation const& unary_operation) override
        {
            utility::Shared<core::Value> value = temporaries_.at(&unary_operation.operand);

            if (!requireType(core::Type::Bool(), value->type(), unary_operation.operand.location))
            {
                abort();
                return;
            }

            switch (unary_operation.op)
            {
                case core::UnaryOperator::NOT:
                    temporaries_.insert_or_assign(&unary_operation.destination, core::Value::makeBool(!value->getBool()));
                    break;
            }
        }

        void visit(bbt::TypeOf const& type_of) override
        {
            utility::Shared<core::Value> value = temporaries_.at(&type_of.expression);
            temporaries_.insert_or_assign(&type_of.destination, core::Value::makeType(value->type()));
        }

        void visit(bbt::OrderedScopeEnter const&) override
        {
            current_scope_ = scopes_.emplace_back(utility::makeOwned<OrderedScope>(this->scope())).get();

            // todo: associate the value storage with the scope so that context switch works better
        }

        void visit(bbt::OrderedScopeExit const&) override
        {
            current_scope_ = current_scope_->parent();

            // todo: destructors and stuff, clean up value storage
            // todo: maybe deleting the scope instance is a good idea?
        }

      private:
        sources::SourceTree& source_tree_;
        core::Reporter& reporter_;
        std::function<utility::Optional<utility::Owned<bbt::UnorderedScope>>(std::filesystem::path const&)> read_unordered_scope_;
        utility::List<utility::Owned<Provider>>& providers_;

        std::function<utility::Optional<utility::Shared<core::Value>>(core::Identifier const&)> provide_ = [this](core::Identifier const& identifier) -> utility::Optional<utility::Shared<core::Value>> {
            for (auto& provider : this->providers_)
            {
                core::Entity const* entity = provider->provide(identifier);
                if (entity != nullptr)
                    return core::Value::makeEntityRef(*entity);
            }

            return std::nullopt;
        };

        void scheduleUnorderedScope(bbt::UnorderedScope const& scope)
        {
            Scope* previous = current_scope_;
            current_scope_ = scopes_.emplace_back(utility::makeOwned<UnorderedScope>(nullptr)).get();

            for (auto const& flow : scope.flows)
            {
                schedule(*flow);
            }

            current_scope_ = previous;
        }

        std::function<void(std::filesystem::path const&)> include_ = [this](std::filesystem::path const& path) {
            utility::Optional<utility::Owned<bbt::UnorderedScope>> scope = read_unordered_scope_(path);

            if (!scope.hasValue())
            {
                abort();
                return;
            }

            bbt::UnorderedScope& scope_ref = **scope;

            roots_.emplace_back(std::move(*scope));

            scheduleUnorderedScope(scope_ref);
        };

        Intrinsics intrinsics_ {source_tree_, reporter_, provide_, include_};

        std::map<core::Entity const*, utility::Shared<core::Value>> variables_ = {};
        std::map<bbt::Temporary const*, utility::Shared<core::Value>> temporaries_ = {};

        std::list<RunPoint> run_points_ = {};
        RunPoint* current_run_point_ = nullptr;
        size_t current_statement_index_ = 0;

        bbt::BasicBlock const* next_ = nullptr;
        utility::Optional<ExecutionResult> execution_result_;

        utility::List<utility::Owned<bbt::UnorderedScope>> roots_;

        std::vector<utility::Owned<Scope>> scopes_ = {};
        Scope* current_scope_ = nullptr;
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
        bbt->schedule(**flow);

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
