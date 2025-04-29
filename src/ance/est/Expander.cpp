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

            (void) reporter_;//todo: use reporter or remove from expander at some point

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

        static void append(Statements& target, Statements&& source)
        {
            target.insert(target.end(), make_move_iterator(source.begin()), make_move_iterator(source.end()));
        }

        static utility::Owned<Statement> wrap(Statements&& statements)
        {
            if (statements.empty()) { return utility::makeOwned<Block>(std::move(statements), core::Location::global()); }

            if (statements.size() == 1 && statements.front()->isCompound())
            {
                return std::move(statements.front());
            }

            core::Location location = statements.front()->location;

            for (auto& statement : statements) { location.extend(statement->location); }

            return utility::makeOwned<Block>(std::move(statements), location);
        }

        void visit(ast::ErrorStatement const& error_statement) override
        {
            setResult(utility::makeOwned<ErrorStatement>(error_statement.location));
        }

        void visit(ast::Block const& block) override
        {
            Statements statements;

            for (auto& statement : block.statements)
            {
                Statements expanded = expand(*statement);
                append(statements, std::move(expanded));
            }

            setResult(utility::makeOwned<Block>(std::move(statements), block.location));
        }

        void visit(ast::Independent const& independent) override
        {
            Statements statements;

            Expansion expansion = expand(*independent.expression);

            append(statements, std::move(expansion.before));
            statements.emplace_back(utility::makeOwned<Independent>(std::move(expansion.center), independent.location));
            append(statements, std::move(expansion.after));

            setResult(std::move(statements));
        }

        void visit(ast::Let const& let) override
        {
            Statements statements;

            utility::Optional<utility::Owned<Expression>> value;
            Statements                                    after;

            if (let.value.hasValue())
            {
                Expansion expansion = expand(**let.value);

                append(statements, std::move(expansion.before));

                value = std::move(expansion.center);
                after = std::move(expansion.after);
            }

            statements.emplace_back(utility::makeOwned<Let>(let.identifier, std::move(value), let.location));

            append(statements, std::move(after));

            setResult(std::move(statements));
        }

        void visit(ast::Assignment const& assignment) override
        {
            Statements statements;

            Expansion expansion = expand(*assignment.value);

            append(statements, std::move(expansion.before));
            statements.emplace_back(utility::makeOwned<Assignment>(assignment.identifier, std::move(expansion.center), assignment.location));
            append(statements, std::move(expansion.after));

            setResult(std::move(statements));
        }

        void visit(ast::If const& if_statement) override
        {
            Statements statements;

            Expansion condition_expansion = expand(*if_statement.condition);
            append(statements, std::move(condition_expansion.before));

            Statements true_statements  = expand(*if_statement.true_part);
            Statements false_statements = if_statement.false_part.hasValue() ? expand(**if_statement.false_part) : Statements();

            statements.emplace_back(utility::makeOwned<If>(std::move(condition_expansion.center),
                                                           wrap(std::move(true_statements)),
                                                           wrap(std::move(false_statements)),
                                                           if_statement.location));

            append(statements, std::move(condition_expansion.after));

            setResult(std::move(statements));
        }

        void visit(ast::Loop const& loop) override
        {
            Statements statements;

            Statements block = expand(*loop.body);
            statements.emplace_back(utility::makeOwned<Loop>(wrap(std::move(block)), loop.location));

            setResult(std::move(statements));
        }

        void visit(ast::Break const& break_statement) override
        {
            Statements statements;
            statements.emplace_back(utility::makeOwned<Break>(break_statement.location));
            setResult(std::move(statements));
        }

        void visit(ast::Continue const& continue_statement) override
        {
            Statements statements;
            statements.emplace_back(utility::makeOwned<Continue>(continue_statement.location));
            setResult(std::move(statements));
        }

        void visit(ast::While const& while_statement) override
        {
            core::Identifier const tmp = core::Identifier::from(while_statement.location);

            Statements loop_body;

            Expansion condition = expand(*while_statement.condition);
            append(loop_body, std::move(condition.before));
            loop_body.emplace_back(utility::makeOwned<Let>(tmp, std::move(condition.center), while_statement.location));
            append(loop_body, std::move(condition.after));

            loop_body.emplace_back(utility::makeOwned<If>(utility::makeOwned<Access>(tmp, while_statement.location),
                                                            utility::makeOwned<Block>(Statements(), while_statement.location),
                                                            utility::makeOwned<Break>(while_statement.location),
                                                            while_statement.location));

            Statements inner_body = expand(*while_statement.body);
            append(loop_body, std::move(inner_body));

            Statements statements;
            statements.emplace_back(utility::makeOwned<Loop>(wrap(std::move(loop_body)), while_statement.location));
            setResult(std::move(statements));
        }

        void visit(ast::ErrorExpression const& error_expression) override
        {
            setResult(utility::makeOwned<ErrorExpression>(error_expression.location));
        }

        void visit(ast::Call const& call) override
        {
            setResult(utility::makeOwned<Call>(call.identifier, call.location));
        }

        void visit(ast::Access const& access) override
        {
            setResult(utility::makeOwned<Access>(access.identifier, access.location));
        }

        void visit(ast::Literal const& literal) override
        {
            setResult(utility::makeOwned<Literal>(literal.value, literal.location));
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
