#include "ExpressionStatement.h"

#include "lang/construct/Function.h"
#include "lang/expression/BuildableExpression.h"
#include "lang/scope/LocalScope.h"

ExpressionStatement::ExpressionStatement(std::unique_ptr<BuildableExpression> expression, lang::Location location)
    : Statement(location)
    , expression_(std::move(expression))
{
    addChild(*expression_);
}

BuildableExpression& ExpressionStatement::expression() const
{
    return *expression_;
}

void ExpressionStatement::setFunction(lang::Function* function)
{
    expression_->setContainingScope(function);
}

void ExpressionStatement::validate(ValidationLogger& validation_logger)
{
    expression_->validate(validation_logger);
}

void ExpressionStatement::doBuild(CompileContext* context)
{
    expression_->build(context);
}
