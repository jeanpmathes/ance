#include "BuildableExpression.h"

#include "compiler/CompileContext.h"

BuildableExpression::BuildableExpression(ance::Location location) : location_(location), containing_scope_ {nullptr} {}

void BuildableExpression::setContainingScope(ance::Scope* scope)
{
    containing_scope_ = scope;
    setScope(scope);
}

void BuildableExpression::setScope(ance::Scope*) {}

void BuildableExpression::build(CompileContext* context)
{
    context->setDebugLocation(location_, containing_scope_);
    doBuild(context);
    context->resetDebugLocation();
}