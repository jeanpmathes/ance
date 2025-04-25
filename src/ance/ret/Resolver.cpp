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
            declarations.insert(let.identifier);
        }

        void visit(est::Assignment const& assignment) override
        {
            visit(*assignment.value);
        }

        void visit(est::If const& if_statement) override
        {
            visit(*if_statement.condition);
            visit(*if_statement.true_block);
            visit(*if_statement.false_block);
        }

        void visit(est::Loop const& loop) override { visit(*loop.body); }

        void visit(est::Break const&) override {}
        void visit(est::Continue const&) override {}

        void visit(est::ErrorExpression const&) override {}
        void visit(est::Call const&) override {}
        void visit(est::Access const&) override {}
        void visit(est::Literal const&) override {}

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

            [[nodiscard]] core::Variable const* expect(core::Identifier const& identifier, core::Reporter& reporter) const
            {
                std::expected<std::reference_wrapper<const core::Variable>, Error> const variable = find(identifier);

                if (variable.has_value())
                {
                    return &variable.value().get();
                }

                switch (variable.error())
                {
                    case Error::Unknown:
                        reporter.error("Cannot resolve name '" + identifier + "'", identifier.location());
                    break;

                    case Error::Blocked:
                        reporter.error("Name '" + identifier + "' blocked by later declaration in scope", identifier.location());
                    break;
                }

                return nullptr;
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

        void visit(est::ErrorStatement const& error_statement) override { setResult(utility::makeOwned<ErrorStatement>(error_statement.location)); }

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
            core::Variable const& variable = current_scope_->declare(let.identifier, let.location);

            utility::Optional<utility::Owned<Expression>> value;

            if (let.value.hasValue()) { value = resolve(**let.value); }

            setResult(utility::makeOwned<Let>(variable, std::move(value), let.location));
        }

        void visit(est::Assignment const& assignment) override
        {
            assert(current_scope_ != nullptr);

            core::Variable const* variable = current_scope_->expect(assignment.identifier, reporter_);
            utility::Owned<Expression> value = resolve(*assignment.value);

            if (variable != nullptr)
            {
                setResult(utility::makeOwned<Assignment>(*variable, std::move(value), assignment.location));
            }
            else
            {
                setResult(utility::makeOwned<ErrorStatement>(assignment.location));
            }
        }

        void visit(est::If const& if_statement) override
        {
            utility::Owned<Expression> condition = resolve(*if_statement.condition);
            utility::Owned<Statement> true_part = resolve(*if_statement.true_block);
            utility::Owned<Statement> false_part = resolve(*if_statement.false_block);

            setResult(utility::makeOwned<If>(std::move(condition), std::move(true_part), std::move(false_part), if_statement.location));
        }

        void visit(est::Loop const& loop) override
        {
            utility::Owned<Statement> body = resolve(*loop.body);

            setResult(utility::makeOwned<Loop>(std::move(body), loop.location));
        }

        void visit(est::Break const& break_statement) override { setResult(utility::makeOwned<Break>(break_statement.location)); }

        void visit(est::Continue const& continue_statement) override { setResult(utility::makeOwned<Continue>(continue_statement.location)); }

        void visit(est::ErrorExpression const& error_expression) override { setResult(utility::makeOwned<ErrorExpression>(error_expression.location)); }

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

                setResult(utility::makeOwned<ErrorExpression>(call.location));
            }
        }

        void visit(est::Access const& access) override
        {
            assert(current_scope_ != nullptr);

            core::Variable const* variable = current_scope_->expect(access.identifier, reporter_);

            if (variable != nullptr)
            {
                setResult(utility::makeOwned<Access>(*variable, access.location));
            }
            else
            {
                setResult(utility::makeOwned<ErrorExpression>(access.location));
            }
        }

        void visit(est::Literal const& literal) override
        {
            setResult(utility::makeOwned<Constant>(literal.value, literal.location));
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
