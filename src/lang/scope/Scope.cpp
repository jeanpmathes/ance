#include "Scope.h"

#include "lang/ApplicationVisitor.h"
#include "lang/scope/LocalScope.h"
#include "lang/type/Type.h"

lang::LocalScope* lang::Scope::asLocalScope()
{
    return nullptr;
}

std::string lang::Scope::getTemporaryName()
{
    return "$temp" + std::to_string(temp_name_counter_++);
}

std::unique_ptr<lang::LocalScope> lang::Scope::makeLocalScope()
{
    auto local_scope = std::make_unique<lang::LocalScope>(this);
    addChild(*local_scope);

    onSubScope(local_scope.get());

    return local_scope;
}

void lang::Scope::addType(lang::ResolvingHandle<lang::Type> type)
{
    if (!type->isDefined()) { registerUsage(type); }
}

void lang::Scope::onSubScope(lang::LocalScope*) {}

