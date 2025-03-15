#include "Expander.h"

#include "ance/core/Scope.h"

#include "ance/ast/Node.h"
#include "ance/est/Node.h"

struct ance::est::Expander::Implementation
{
    using Statements = utility::List<utility::Owned<Statement>>;

    struct Expansion
    {
        Statements                 before;
        utility::Owned<Expression> center;
        Statements                 after;
    };

    class AST final : public ast::Visitor
    {
      public:
        using Visitor::visit;

        explicit AST(core::Reporter& reporter) : reporter_(reporter) {}
        ~AST() override = default;

        void setResult(utility::Owned<Statement> statement)
        {
            assert(!statement_expansion_.hasValue() && !expression_expansion_.hasValue());

            Statements statements;
            statements.emplace_back(std::move(statement));

            statement_expansion_  = std::move(statements);
            expression_expansion_ = std::nullopt;
        }

        void setResult(Statements statements)
        {
            assert(!statement_expansion_.hasValue() && !expression_expansion_.hasValue());

            statement_expansion_  = std::move(statements);
            expression_expansion_ = std::nullopt;
        }

        void setResult(utility::Owned<Expression> expression)
        {
            assert(!statement_expansion_.hasValue() && !expression_expansion_.hasValue());

            statement_expansion_  = std::nullopt;
            expression_expansion_ = {.before = {}, .center = std::move(expression), .after = {}};
        }

        Statements expand(ast::Statement const& statement)
        {
            visit(statement);

            (void)reporter_;//todo: use reporter or remove from expander at some point

            assert(statement_expansion_.hasValue());

            Statements result    = std::move(*statement_expansion_);
            statement_expansion_ = std::nullopt;

            return result;
        }

        Expansion expand(ast::Expression const& expression)
        {
            visit(expression);

            assert(expression_expansion_.hasValue());

            Expansion result      = std::move(*expression_expansion_);
            expression_expansion_ = std::nullopt;

            return result;
        }

        void visit(ast::ErrorStatement const& error_statement) override { setResult(utility::makeOwned<ErrorStatement>(error_statement.location)); }

        void visit(ast::Block const& block) override
        {
            utility::List<utility::Owned<Statement>> statements;

            for (auto& statement : block.statements)
            {
                Statements expanded = expand(*statement);
                statements.insert(statements.end(),
                                  make_move_iterator(expanded.begin()),
                                  make_move_iterator(expanded.end()));
            }

            setResult(utility::makeOwned<Block>(std::move(statements), block.location));
        }

        void visit(ast::Independent const& independent) override
        {
            Statements statements;

            Expansion expansion = expand(*independent.expression);

            statements.insert(statements.end(),
                              make_move_iterator(expansion.before.begin()),
                              make_move_iterator(expansion.before.end()));
            statements.emplace_back(
                utility::makeOwned<Independent>(std::move(expansion.center), independent.location));
            statements.insert(statements.end(),
                              make_move_iterator(expansion.after.begin()),
                              make_move_iterator(expansion.after.end()));

            setResult(std::move(statements));
        }

        void visit(ast::Let const& let) override
        {
            Statements statements;

            utility::Optional<utility::Owned<Expression>> value;

            if (let.value.hasValue())
            {
                auto [before, center, after] = expand(**let.value);

                statements.insert(statements.end(),
                                make_move_iterator(before.begin()),
                                make_move_iterator(before.end()));

                value = std::move(center);

                statements.insert(statements.end(),
                                make_move_iterator(after.begin()),
                                make_move_iterator(after.end()));
            }

            statements.emplace_back(utility::makeOwned<Let>(let.variable, std::move(value), let.location));

            setResult(std::move(statements));
        }

        void visit(ast::ErrorExpression const& error_expression) override { setResult(utility::makeOwned<ErrorExpression>(error_expression.location)); }

        void visit(ast::Call const& call) override
        {
            setResult(utility::makeOwned<Call>(call.identifier, call.location));
        }

        void visit(ast::Access const& access) override
        {
            setResult(utility::makeOwned<Access>(access.identifier, access.location));
        }

      private:
        utility::Optional<Statements> statement_expansion_;
        utility::Optional<Expansion>  expression_expansion_;

        core::Reporter& reporter_;
    };

    explicit Implementation(core::Reporter& reporter) : reporter_(reporter) {}

    utility::Owned<Statement> expand(ast::Statement const& statement)
    {
        utility::Owned<AST> ast = utility::makeOwned<AST>(reporter_);

        Statements statements = ast->expand(statement);

        return utility::makeOwned<Block>(std::move(statements), statement.location);
    }

private:
    core::Reporter& reporter_;
};

ance::est::Expander::Expander(core::Reporter& reporter) : implementation_(utility::makeOwned<Implementation>(reporter)) {}

ance::est::Expander::~Expander() = default;

ance::utility::Owned<ance::est::Statement> ance::est::Expander::expand(ast::Statement const& statement)
{
    return implementation_->expand(statement);
}
