#include "Runner.h"

#include <iostream>
#include <map>
#include <set>
#include <expected>

#include "ance/core/Intrinsic.h"
#include "ance/core/Function.h"

#include "ance/bbt/Node.h"
#include "ance/cet/Node.h"
#include "ance/core/Value.h"

struct ance::cet::Runner::Implementation
{
    class Variable
    {
    public:
        Variable(core::Identifier const& identifier, core::Type const& type)
            : identifier_(identifier), type_(type)
        {
        }

        [[nodiscard]] core::Identifier const& identifier() const { return identifier_; }
        [[nodiscard]] core::Type const& type() const { return type_; }

    private:
        core::Identifier identifier_;
        core::Type const& type_;
    };

    class Scope
    {
      protected:
        explicit Scope(Scope* parent) : parent_(parent)
        {
        }

      public:
        virtual ~Scope() = default;

        utility::Optional<std::reference_wrapper<Variable const>> declare(core::Identifier const& identifier, core::Type const& type, core::Location const& location, core::Reporter& reporter)
        {
            if (!canDeclare(identifier))
            {
                reporter.error("Declaring '" + identifier + "' in this scope would block previous access to outside of the scope", location);
                return std::nullopt;
            }

            utility::Owned<Variable> variable = utility::makeOwned<Variable>(identifier, type);
            Variable const& variable_ref = *variable;

            onDeclare(std::move(variable));

            return std::cref(variable_ref);
        }

        enum class Error
        {
            Unknown
        };

        [[nodiscard]] std::expected<std::reference_wrapper<Variable const>, Error> find(core::Identifier const& identifier)
        {
            // todo: when using resolving for intrinsics/functions, instead of adding a global scope, the find method should take a list of providers to use when top of the scope chain is reached
            // todo: when adding the functions then also add a Value base class for function and variable and scopes should hold Values only
            // todo: essentially resolving of functions / values should use the same logic - a resolve intrinsic, and intrinsics are placed inside function when they should be part of resolution
            // todo: the nodes should hold the correct type - meaning that this type checking is done in the resolver

            return onFind(identifier).or_else([&](Error const error) -> std::expected<std::reference_wrapper<Variable const>, Error> {
                if (error == Error::Unknown && parent_ != nullptr) { return parent_->find(identifier); }

                return std::unexpected(error);
            });
        }

        [[nodiscard]] Variable const* expect(core::Identifier const& identifier, core::Reporter& reporter)
        {
            std::expected<std::reference_wrapper<Variable const>, Error> const variable = find(identifier);

            if (variable.has_value()) { return &variable.value().get(); }

            switch (variable.error())
            {
                case Error::Unknown:
                    reporter.error("Cannot resolve name '" + identifier + "'", identifier.location());
                    break;
            }

            return nullptr;
        }

      protected:
        [[nodiscard]] virtual bool                                                                             canDeclare(core::Identifier const& identifier) const = 0;
        virtual void                                                                             onDeclare(utility::Owned<Variable> variable)   = 0;
        [[nodiscard]] virtual std::expected<std::reference_wrapper<Variable const>, Error> onFind(core::Identifier const& identifier)  = 0;

      private:
        Scope*           parent_;
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

        [[nodiscard]] std::expected<std::reference_wrapper<Variable const>, Error> onFind(core::Identifier const& identifier) override
        {
            if (active_variables_.contains(identifier)) { return active_variables_.at(identifier); }

            outer_identifiers_.insert(identifier);

            return std::unexpected(Error::Unknown);
        }

      private:
        std::vector<utility::Owned<Variable>> all_variables_ = {};
        std::map<core::Identifier, std::reference_wrapper<Variable const>> active_variables_ = {};
        std::set<core::Identifier> outer_identifiers_ = {};
    };

    class Intrinsics final : core::IntrinsicVisitor
    {
    public:
        using IntrinsicVisitor::visit;

        explicit Intrinsics(core::Reporter& reporter) : reporter_(reporter) {}

        void run(core::Intrinsic const& intrinsic, utility::List<utility::Shared<core::Value>> const& arguments, core::Location const& location)
        {
            location_ = location;
            arguments_ = &arguments;

            this->visit(intrinsic);

            location_ = core::Location::global();
            arguments_ = nullptr;
        }

        void visit(core::Dynamic const& dynamic) override
        {
            reporter_.error("Unsupported intrinsic '" + dynamic.identifier() + "'", location_);
        }

        void visit(core::NoOp const&) override
        {
            // Do nothing.
        }

    private:
        core::Reporter& reporter_;

        core::Location location_ = core::Location::global();
        utility::List<utility::Shared<core::Value>> const* arguments_ = nullptr;
    };

    class BBT final : public bbt::Visitor
    {
    public:
        using Visitor::visit;

        explicit BBT(core::Reporter& reporter) : reporter_(reporter) {}
        ~BBT() override = default;

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

            size_t const arity = signature.types().size();
            size_t const argument_count = arguments.size();

            if (arity != argument_count)
            {
                reporter_.error("Call to '" + signature.name() + "' with wrong number of arguments: " +
                                " expected " + std::to_string(arity) +
                                " but got " + std::to_string(argument_count),
                                location);
                ok = false;
            }

            for (size_t i = 0; i < argument_count; ++i)
            {
                auto const& argument = arguments[i];
                auto const& argument_value = temporaries_.at(&argument.get());
                auto const& type = signature.types()[i].get();

                ok &= requireType(type, argument_value->type(), argument.get().location);
            }

            return ok;
        }

        void abort()
        {
            encountered_error_ = true;
            next_ = nullptr;
        }

        void run(bbt::BasicBlock const& basic_block)
        {
            next_ = &basic_block;

            while (next_ != nullptr)
            {
                visit(*next_);
            }

            // todo: when creating new basic blocks here, also implement simplification / already output simplified blocks for compilation
            // todo: maybe simplification code should be shared in some way?
        }

        void run(bbt::Statement const& statement)
        {
            visit(statement);
        }

        [[nodiscard]] Scope* scope()
        {
            if (scopes_.empty()) return nullptr;

            return scopes_.back().get();
        }

        void visit(bbt::Flow const& flow) override
        {
            run(flow.entry);
        }

        void visit(bbt::BasicBlock const& basic_block) override
        {
            for (auto& statement : basic_block.statements)
            {
                run(*statement);

                if (encountered_error_)
                    return;
            }

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

        void visit(bbt::Declare const& declare) override
        {
            utility::Shared<core::Value> type = temporaries_.at(&declare.type);

            if (!requireType(core::Type::Self(), type->type(), declare.type.location))
            {
                abort();
                return;
            }

            utility::Shared<core::Value> value = core::Value::makeDefault(type->getType());

            if (declare.value != nullptr)
            {
                utility::Shared<core::Value> assigned = temporaries_.at(declare.value);

                if (!requireType(type->getType(), assigned->type(), declare.value->location))
                {
                    abort();
                    return;
                }

                value = assigned;
            }

            auto variable = scope()->declare(declare.identifier, type->getType(), declare.location, reporter_);

            if (variable.hasValue())
            {
                variables_.insert_or_assign(&variable.value().get(), value);
            }
            else
            {
                abort();
            }
        }

        void visit(bbt::Store const& store) override
        {
            utility::Shared<core::Value> value = temporaries_.at(&store.value);

            Variable const* variable = scope()->expect(store.identifier, reporter_);

            if (variable == nullptr)
            {
                abort();
                return;
            }

            core::Type const& type = variable->type();

            if (!requireType(type, value->type(), store.value.location))
            {
                abort();
                return;
            }

            variables_.insert_or_assign(variable, value);
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

            intrinsics_.run(intrinsic.intrinsic, arguments, intrinsic.location);
            temporaries_.insert_or_assign(&intrinsic.destination, core::Value::makeUnit());
        }

        void visit(bbt::Call const& call) override
        {
            if (!requireSignature(call.called.signature(), call.arguments, call.location))
            {
                abort();
                return;
            }

            utility::List<utility::Shared<core::Value>> arguments = {};
            for (auto argument : call.arguments) { arguments.emplace_back(temporaries_.at(&argument.get())); }

            call.called.run(arguments);
            temporaries_.insert_or_assign(&call.destination, core::Value::makeUnit());
        }

        void visit(bbt::Read const& read) override
        {
            Variable const* variable = scope()->expect(read.identifier, reporter_);

            if (variable == nullptr)
            {
                abort();
                return;
            }

            utility::Shared<core::Value> value = variables_.at(variable);
            temporaries_.insert_or_assign(&read.destination, value);
        }

        void visit(bbt::Constant const& constant) override
        {
            temporaries_.insert_or_assign(&constant.destination, constant.value->clone());
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

        void visit(bbt::ScopeEnter const&) override
        {
            utility::Owned<Scope> scope = utility::makeOwned<OrderedScope>(this->scope());
            scopes_.emplace_back(std::move(scope));

            // todo: make value storage also part of the scope so it is cleaned up when scope exits
        }

        void visit(bbt::ScopeExit const&) override
        {
            scopes_.pop_back();

            // todo: destructors and stuff
        }

      private:
        core::Reporter& reporter_;

        Intrinsics intrinsics_ {reporter_};

        std::map<Variable const*, utility::Shared<core::Value>> variables_ = {};
        std::map<bbt::Temporary const*, utility::Shared<core::Value>> temporaries_ = {};
        std::vector<utility::Owned<Scope>> scopes_ = {};

        bbt::BasicBlock const* next_ = nullptr;
        bool encountered_error_ = false;
    };

    explicit Implementation(core::Reporter& reporter) : reporter_(reporter) {}

    utility::Owned<Unit> run(bbt::Flow const& flow)
    {
        utility::Owned<Unit> unit = utility::makeOwned<Unit>();

        utility::Owned<BBT> bbt = utility::makeOwned<BBT>(reporter_);
        bbt->visit(flow);

        return unit;
    }

private:
    core::Reporter& reporter_;
};

ance::cet::Runner::Runner(core::Reporter& reporter) : implementation_(utility::makeOwned<Implementation>(reporter)) {}

ance::cet::Runner::~Runner() = default;

ance::utility::Owned<ance::cet::Unit> ance::cet::Runner::run(bbt::Flow const& flow)
{
    return implementation_->run(flow);
}
