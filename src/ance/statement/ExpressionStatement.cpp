#include "ExpressionStatement.h"

#include "ance/construct/DefinedFunction.h"
#include "ance/expression/BuildableExpression.h"
#include "ance/scope/LocalScope.h"

ExpressionStatement::ExpressionStatement(BuildableExpression* expression, ance::Location location)
    : Statement(location)
    , expression_(expression)
{
    addChild(*expression);
}

void ExpressionStatement::setFunction(ance::DefinedFunction* function)
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

bool ExpressionStatement::accept(ance::ApplicationVisitor& visitor)
{
    return visitor.visitExpressionStatement(*this);
}
