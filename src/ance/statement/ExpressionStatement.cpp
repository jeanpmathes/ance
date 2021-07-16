#include "ExpressionStatement.h"

#include "BuildableExpression.h"
#include "DefinedFunction.h"
#include "LocalScope.h"

ExpressionStatement::ExpressionStatement(
    BuildableExpression* expression,
    unsigned             line,
    unsigned             column)
    : Statement(line, column), expression_(expression)
{
}

void ExpressionStatement::setFunction(ance::DefinedFunction* function)
{
    expression_->setScope(function->getScope());
}

void ExpressionStatement::build(CompileContext* context)
{
    expression_->build(context);
}
