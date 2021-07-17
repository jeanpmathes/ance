#include "Discard.h"

void Discard::setScope(ance::Scope*)
{
}

void Discard::assign(ance::Value* value, CompileContext* context)
{
    value->buildNativeValue(context);
}
