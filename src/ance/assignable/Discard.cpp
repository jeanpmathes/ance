#include "Discard.h"

Discard::Discard(ance::Location location) : Assignable(location) {}

void Discard::setScope(ance::Scope*) {}

void Discard::validate(ValidationLogger&) {}

void Discard::doBuild(CompileContext* context)
{
    assigned()->buildNativeValue(context);
}
