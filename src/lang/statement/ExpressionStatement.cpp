#include "ExpressionStatement.h"

#include "lang/ApplicationVisitor.h"

ExpressionStatement::ExpressionStatement(Owned<Expression> expression, lang::Location location)
    : Statement(location)
    , expression_(std::move(expression))
{
    addSubexpression(*expression_);
}

Expression const& ExpressionStatement::expression() const
{
    return *expression_;
}

void ExpressionStatement::validate(ValidationLogger& validation_logger) const
{
    expression_->validate(validation_logger);
}

Statements ExpressionStatement::expandWith(Expressions subexpressions, Statements, lang::Context&) const
{
    Statements statements;

    statements.emplace_back(makeOwned<ExpressionStatement>(std::move(subexpressions[0]), location()));

    return statements;
}
