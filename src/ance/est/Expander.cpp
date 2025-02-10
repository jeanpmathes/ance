#include "Expander.h"

#include <array>

#include "ance/ast/Node.h"
#include "ance/est/Node.h"

namespace ance
{
    using Statements = utility::List<utility::Owned<est::Statement>>;

    struct Expansion {
        Statements                      before;
        utility::Owned<est::Expression> center;
        Statements                      after;
    };

    class AST final : public ast::Visitor
    {
      public:
        using Visitor::visit;

        void setResult(utility::Owned<est::Statement> statement)
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

        void setResult(utility::Owned<est::Expression> expression)
        {
            assert(!statement_expansion_.hasValue() && !expression_expansion_.hasValue());

            statement_expansion_  = std::nullopt;
            expression_expansion_ = {.before = {}, .center = std::move(expression), .after = {}};
        }

        Statements expand(ast::Statement const& statement)
        {
            visit(statement);

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

        void visit(ast::ErrorStatement const&) override { setResult(utility::makeOwned<est::ErrorStatement>()); }

        void visit(ast::Block const& block) override
        {
            utility::List<utility::Owned<est::Statement>> statements;

            for (auto& statement : block.statements)
            {
                Statements expanded = expand(*statement);
                statements.insert(statements.end(),
                                  make_move_iterator(expanded.begin()),
                                  make_move_iterator(expanded.end()));
            }

            setResult(utility::makeOwned<est::Block>(std::move(statements), block.location));
        }

        void visit(ast::Independent const& independent) override
        {
            Statements statements;

            Expansion expansion = expand(*independent.expression);

            statements.insert(statements.end(),
                              make_move_iterator(expansion.before.begin()),
                              make_move_iterator(expansion.before.end()));
            statements.emplace_back(
                utility::makeOwned<est::Independent>(std::move(expansion.center), independent.location));
            statements.insert(statements.end(),
                              make_move_iterator(expansion.after.begin()),
                              make_move_iterator(expansion.after.end()));

            setResult(std::move(statements));
        }

        void visit(ast::ErrorExpression const&) override { setResult(utility::makeOwned<est::ErrorExpression>()); }

        void visit(ast::Call const& call) override
        {
            setResult(utility::makeOwned<est::Call>(call.identifier, call.location));
        }

      private:
        utility::Optional<Statements> statement_expansion_;
        utility::Optional<Expansion>  expression_expansion_;
    };
}

struct ance::est::Expander::Implementation {
    utility::Owned<Statement> expand(ast::Statement const& statement)
    {
        AST ast;

        Statements statements = ast.expand(statement);

        return utility::makeOwned<Block>(std::move(statements), statement.location);
    }
};

ance::est::Expander::Expander() : implementation_(utility::makeOwned<Implementation>()) {}

ance::est::Expander::~Expander() = default;

ance::utility::Owned<ance::est::Statement> ance::est::Expander::expand(ast::Statement const& statement)
{
    return implementation_->expand(statement);
}
