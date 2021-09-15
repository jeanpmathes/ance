#include "BuildableExpression.h"

#include "compiler/CompileContext.h"

void BuildableExpression::setContainingScope(ance::Scope* scope)
{
    containing_scope_ = scope;
    setScope(scope);
}

void BuildableExpression::setScope(ance::Scope*) {}

ance::Scope* BuildableExpression::scope() const
{
    return containing_scope_;
}

void BuildableExpression::build(CompileContext* context)
{
    context->setDebugLocation(location(), containing_scope_);
    doBuild(context);
    context->resetDebugLocation();
}