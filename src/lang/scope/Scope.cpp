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

void lang::Scope::addDependency(lang::ResolvingHandle<lang::Variable> variable)
{
    assert(variable->isDefined());

    if (variable->scope() == this) return;

    variable_dependencies_.insert(variable);

    scope()->addDependency(variable);
}

void lang::Scope::addDependency(lang::ResolvingHandle<lang::Function> function)
{
    assert(function->isDefined());

    if (function->scope() == this) return;

    function_dependencies_.insert(function);

    scope()->addDependency(function);
}

std::set<lang::ResolvingHandle<lang::Variable>> lang::Scope::getVariableDependencies() const
{
    return variable_dependencies_;
}

std::set<lang::ResolvingHandle<lang::Function>> lang::Scope::getFunctionDependencies() const
{
    return function_dependencies_;
}
