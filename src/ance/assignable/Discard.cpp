#include "Discard.h"

#include "ance/ApplicationVisitor.h"
#include "ance/construct/value/Value.h"

Discard::Discard(ance::Location location) : Assignable(location) {}

void Discard::setScope(ance::Scope*) {}

void Discard::validate(ValidationLogger&) {}

void Discard::doBuild(CompileContext* context)
{
    assigned()->buildNativeValue(context);
}

bool Discard::accept(ance::ApplicationVisitor& visitor)
{
    return visitor.visitDiscard(*this);
}