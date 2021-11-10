#include "Scope.h"

#include "ance/type/Type.h"

void ance::Scope::addType(ance::ResolvingHandle<ance::Type> type)
{
    if (!type->isDefined()) { registerUsage(type); }
}
