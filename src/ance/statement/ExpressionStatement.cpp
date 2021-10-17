#include "ExpressionStatement.h"

#include "ance/ApplicationVisitor.h"
#include "ance/construct/DefinedFunction.h"
#include "ance/expression/BuildableExpression.h"
#include "ance/scope/LocalScope.h"

ExpressionStatement::ExpressionStatement(std::unique_ptr<BuildableExpression> expression, ance::Location location)
    : Statement(location)
    , expression_(std::move(expression))
{
    addChild(*expression_);
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
