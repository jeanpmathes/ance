#include "ExpressionStatement.h"

#include "ance/construct/DefinedFunction.h"
#include "ance/expression/BuildableExpression.h"
#include "ance/scope/LocalScope.h"

ExpressionStatement::ExpressionStatement(BuildableExpression* expression, ance::Location location)
    : Statement(location)
    , expression_(expression)
{}

void ExpressionStatement::setFunction(ance::DefinedFunction* function)
{
    expression_->setContainingScope(function);
}

void ExpressionStatement::doBuild(CompileContext* context)
{
    expression_->build(context);
}
