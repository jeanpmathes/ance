#include "ExpressionStatement.h"

#include "ance/construct/Function.h"
#include "ance/expression/BuildableExpression.h"
#include "ance/scope/LocalScope.h"

ExpressionStatement::ExpressionStatement(std::unique_ptr<BuildableExpression> expression, ance::Location location)
    : Statement(location)
    , expression_(std::move(expression))
{}

void ExpressionStatement::setFunction(ance::Function* function)
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

