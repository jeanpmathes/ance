#include "Assignable.h"

#include "compiler/CompileContext.h"

Assignable::Assignable(ance::Location location) : location_(location) {}

void Assignable::setContainingScope(ance::Scope* scope)
{
    containing_scope_ = scope;
    setScope(scope);
}

void Assignable::validate() {}

void Assignable::assign(ance::Value* value, CompileContext* context)
{
    context->setDebugLocation(location_, containing_scope_);
    buildAssignment(value, context);
    context->resetDebugLocation();
}
