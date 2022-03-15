#include "Scope.h"

#include "lang/scope/LocalScope.h"
#include "lang/type/Type.h"

lang::LocalScope* lang::Scope::getLocalScope()
{
    return nullptr;
}

std::unique_ptr<lang::LocalScope> lang::Scope::makeLocalScope()
{
    auto local_scope = std::make_unique<lang::LocalScope>(this);
    addChild(*local_scope);

    return local_scope;
}

void lang::Scope::addType(lang::ResolvingHandle<lang::Type> type)
{
    if (!type->isDefined()) { registerUsage(type); }
}
