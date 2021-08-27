#include "Discard.h"

Discard::Discard(ance::Location location) : Assignable(location) {}

void Discard::setScope(ance::Scope*) {}

void Discard::buildAssignment(ance::Value* value, CompileContext* context)
{
    value->buildNativeValue(context);
}
