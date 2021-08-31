#include "Assignable.h"

#include "compiler/CompileContext.h"

Assignable::Assignable(ance::Location location) : location_(location) {}

void Assignable::setContainingScope(ance::Scope* scope)
{
    containing_scope_ = scope;
    setScope(scope);
}

void Assignable::assign(ance::Value* value)
{
    assert(!assigned_value_ && "There may be only one value assigned to an assignable.");
    assigned_value_ = value;
}

void Assignable::build(CompileContext* context)
{
    context->setDebugLocation(location_, containing_scope_);
    doBuild(context);
    context->resetDebugLocation();
}

ance::Value* Assignable::assigned()
{
    return assigned_value_;
}

ance::Location Assignable::location()
{
    return location_;
}
