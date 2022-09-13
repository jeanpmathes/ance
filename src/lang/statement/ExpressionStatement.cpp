#include "ExpressionStatement.h"

#include "lang/ApplicationVisitor.h"
#include "lang/construct/Function.h"
#include "lang/expression/BuildableExpression.h"

ExpressionStatement::ExpressionStatement(std::unique_ptr<BuildableExpression> expression, lang::Location location)
    : Statement(location)
    , expression_(std::move(expression))
{
    addSubexpression(*expression_);
}

BuildableExpression& ExpressionStatement::expression() const
{
    return *expression_;
}

void ExpressionStatement::validate(ValidationLogger& validation_logger) const
{
    expression_->validate(validation_logger);
}

Statements ExpressionStatement::expandWith(Expressions subexpressions, Statements) const
{
    Statements statements;

    auto* expression = dynamic_cast<BuildableExpression*>(subexpressions[0].release());

    statements.push_back(
        std::make_unique<ExpressionStatement>(std::unique_ptr<BuildableExpression>(expression), location()));

    return statements;
}

void ExpressionStatement::doBuild(CompileContext& context)
{
    expression_->build(context);
}

