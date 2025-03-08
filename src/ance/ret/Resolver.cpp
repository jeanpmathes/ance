#include "Resolver.h"

#include <map>
#include <set>
#include <expected>

#include "ance/core/Intrinsic.h"
#include "ance/core/Scope.h"

#include "ance/est/Node.h"
#include "ance/ret/Node.h"

struct ance::ret::Resolver::Implementation
{
    class Declarations final : public est::Visitor
    {
      public:
        using Visitor::visit;

        Declarations() = default;
        ~Declarations() override = default;

        static std::set<core::Identifier> get(est::Block const& block)
        {
            Declarations declarations;
            declarations.visit(block);

            return declarations.declarations;
        }

    protected:
        void visit(est::ErrorStatement const&) override {}

        void visit(est::Block const& block) override
        {
            depth++;

            if (depth <= MAX_DEPTH)
            {
                for (auto& statement : block.statements) { visit(*statement); }
            }

            depth--;
        }

        void visit(est::Independent const& independent) override
        {
            visit(*independent.expression);
        }

        void visit(est::Let const& let) override
        {
            declarations.insert(let.variable);
        }

        void visit(est::ErrorExpression const&) override {}
        void visit(est::Call const&) override {}
        void visit(est::Access const&) override {}

    private:
        std::set<core::Identifier> declarations = {};
        size_t                     depth        = 0;

        constexpr static size_t MAX_DEPTH = 1;
    };

    class EST final : public est::Visitor
    {
      public:
        using Visitor::visit;

        EST(core::Reporter&                                                                  reporter,
            std::map<core::Identifier, std::reference_wrapper<core::Intrinsic const>> const& intrinsics)
            : reporter_(reporter)
            , intrinsics_(intrinsics)
        {}
        ~EST() override = default;

        void setResult(utility::Owned<Statement> statement)
        {
            assert(!resolved_statement_.hasValue() && !resolved_expression_.hasValue());

            resolved_statement_  = std::move(statement);
            resolved_expression_ = std::nullopt;
        }

        void setResult(utility::Owned<Expression> expression)
        {
            assert(!resolved_statement_.hasValue() && !resolved_expression_.hasValue());

            resolved_statement_  = std::nullopt;
            resolved_expression_ = std::move(expression);
        }

        utility::Owned<Statement> resolve(est::Statement const& statement)
        {
            visit(statement);

            assert(resolved_statement_.hasValue());

            utility::Owned<Statement> result = std::move(*resolved_statement_);
            resolved_statement_              = std::nullopt;

            return result;
        }

        utility::Owned<Expression> resolve(est::Expression const& expression)
        {
            visit(expression);

            assert(resolved_expression_.hasValue());

            utility::Owned<Expression> result = std::move(*resolved_expression_);
            resolved_expression_              = std::nullopt;

            return result;
        }

        class Scope
        {
        protected:
            Scope(Scope const* parent, utility::Owned<core::Scope> scope) : parent_(parent), scope_(std::move(scope)) {}

        public:
            virtual ~Scope() = default;

            core::Scope& scope() { return *scope_; }

            core::Variable const& declare(core::Identifier const& identifier, core::Location const& location)
            {
                core::Variable const& variable = scope_->addVariable(identifier, location);

                onDeclare(variable);

                return variable;
            }

            enum class Error
            {
                Unknown,
                Blocked
            };

            [[nodiscard]] std::expected<std::reference_wrapper<const core::Variable>, Error> find(core::Identifier const& identifier) const
            {
                return onFind(identifier).or_else([&](Error const error) -> std::expected<std::reference_wrapper<const core::Variable>, Error> {
                    if (error == Error::Unknown && parent_ != nullptr)
                    {
                        return parent_->find(identifier);
                    }

                    return std::unexpected(error);
                });
            }

            static utility::Owned<core::Scope> decompose(utility::Owned<Scope> scope)
            {
                return std::move(scope->scope_);
            }

        protected:
            virtual void onDeclare(core::Variable const& variable) = 0;
            [[nodiscard]] virtual std::expected<std::reference_wrapper<const core::Variable>, Error> onFind(core::Identifier const& identifier) const = 0;

        private:
            Scope const* parent_;
            utility::Owned<core::Scope> scope_;
        };

        class OrderedScope final : public Scope
        {
        public:
            OrderedScope(std::set<core::Identifier> declarations, Scope const* parent, utility::Owned<core::Scope> scope)
                : Scope(parent, std::move(scope))
                , declarations_(std::move(declarations))
            {}

            ~OrderedScope() override = default;

            static utility::Owned<Scope> create(est::Block const& block, Scope* parent)
            {
                std::set<core::Identifier> const declarations = Declarations::get(block);

                return utility::makeOwned<OrderedScope>(declarations, parent, parent != nullptr
                    ? parent->scope().createChild()
                    : utility::makeOwned<core::Scope>());
            }

        protected:
            void onDeclare(core::Variable const& variable) override
            {
                active_variables_.emplace(variable.identifier(), std::cref(variable));
            }

            [[nodiscard]] std::expected<std::reference_wrapper<const core::Variable>, Error> onFind(core::Identifier const& identifier) const override
            {
                if (active_variables_.contains(identifier))
                {
                    return active_variables_.at(identifier);
                }

                if (declarations_.contains(identifier))
                {
                    return std::unexpected(Error::Blocked);
                }

                return std::unexpected(Error::Unknown);
            }

        private:
            std::set<core::Identifier> const declarations_;

            std::map<core::Identifier, std::reference_wrapper<const core::Variable>> active_variables_ = {};
        };

        static utility::Owned<core::Scope> createScope(utility::Optional<utility::Owned<core::Scope>>& parent)
        {
            if (parent.hasValue())
            {
                return (*parent)->createChild();
            }

            return utility::makeOwned<core::Scope>();
        }

        void visit(est::ErrorStatement const&) override { setResult(utility::makeOwned<ErrorStatement>()); }

        void visit(est::Block const& block) override
        {
            Scope* parent_scope = current_scope_;
            utility::Owned<Scope> scope = OrderedScope::create(block, parent_scope);
            current_scope_ = scope.get();

            utility::List<utility::Owned<Statement>> statements;
            for (auto& statement : block.statements)
            {
                auto resolved = resolve(*statement);
                statements.emplace_back(std::move(resolved));
            }

            current_scope_ = parent_scope;
            utility::Owned<core::Scope> block_scope = OrderedScope::decompose(std::move(scope));

            setResult(utility::makeOwned<Block>(std::move(block_scope), std::move(statements), block.location));
        }

        void visit(est::Independent const& independent) override
        {
            auto resolved = resolve(*independent.expression);

            setResult(utility::makeOwned<Independent>(std::move(resolved), independent.location));
        }

        void visit(est::Let const& let) override
        {
            assert(current_scope_ != nullptr);
            core::Variable const& variable = current_scope_->declare(let.variable, let.location);

            utility::Optional<utility::Owned<Expression>> value;

            if (let.value.hasValue()) { value = resolve(**let.value); }

            setResult(utility::makeOwned<Let>(variable, std::move(value), let.location));
        }

        void visit(est::ErrorExpression const&) override { setResult(utility::makeOwned<ErrorExpression>()); }

        void visit(est::Call const& call) override
        {
            // todo: when using resolving for intrinsics, instead of adding a global scope, the find method should take a list of providers to use when top of the scope chain is reached
            // todo: also when adding the functions then also add an entity base class for function and variable and scopes should hold entities only
            // todo: the nodes should hold the correct type - meaning that this type checking is done in the resolver

            if (intrinsics_.contains(call.identifier))
            {
                setResult(utility::makeOwned<Intrinsic>(intrinsics_.at(call.identifier).get(), call.location));
            }
            else
            {
                reporter_.error("Unknown intrinsic '" + call.identifier + "'", call.identifier.location());

                setResult(utility::makeOwned<ErrorExpression>());
            }
        }

        void visit(est::Access const& access) override
        {
            assert(current_scope_ != nullptr);

            std::expected<std::reference_wrapper<const core::Variable>, Scope::Error> const variable = current_scope_->find(access.identifier);

            if (variable.has_value())
            {
                setResult(utility::makeOwned<Access>(variable.value().get(), access.location));
            }
            else
            {
                switch (variable.error())
                {
                    case Scope::Error::Unknown:
                        reporter_.error("Cannot resolve name '" + access.identifier + "'", access.identifier.location());
                        break;

                    case Scope::Error::Blocked:
                        reporter_.error("Name '" + access.identifier + "' blocked by later declaration in scope", access.identifier.location());
                        break;
                }

                setResult(utility::makeOwned<ErrorExpression>());
            }
        }

      private:
        core::Reporter&                                                                  reporter_;
        std::map<core::Identifier, std::reference_wrapper<core::Intrinsic const>> const& intrinsics_;

        Scope* current_scope_ = nullptr;

        utility::Optional<utility::Owned<Statement>>  resolved_statement_  = std::nullopt;
        utility::Optional<utility::Owned<Expression>> resolved_expression_ = std::nullopt;
    };

    explicit Implementation(core::Reporter& reporter) : reporter_(reporter) {}

    void add(core::Intrinsic const& intrinsic) { intrinsics_.emplace(intrinsic.identifier(), std::cref(intrinsic)); }

    utility::Owned<Statement> resolve(est::Statement const& statement)
    {
        utility::Owned<EST> est = utility::makeOwned<EST>(reporter_, intrinsics_);

        return est->resolve(statement);
    }

  private:
    core::Reporter& reporter_;

    std::map<core::Identifier, std::reference_wrapper<core::Intrinsic const>> intrinsics_ = {};
};

ance::ret::Resolver::Resolver(core::Reporter& reporter) : implementation_(utility::makeOwned<Implementation>(reporter))
{}

ance::ret::Resolver::~Resolver() = default;

void ance::ret::Resolver::add(core::Intrinsic const& intrinsic)
{
    implementation_->add(intrinsic);
}

ance::utility::Owned<ance::ret::Statement> ance::ret::Resolver::resolve(est::Statement const& statement)
{
    return implementation_->resolve(statement);
}
