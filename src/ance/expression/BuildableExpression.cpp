#include "BuildableExpression.h"

BuildableExpression::BuildableExpression(ance::Location location) : location_(location) {}

void BuildableExpression::setContainingScope(ance::Scope* scope)
{
    containing_scope_ = scope;
    setScope(scope);
}

void BuildableExpression::setScope(ance::Scope*) {}
