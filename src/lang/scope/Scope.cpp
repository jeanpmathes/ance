#include "Scope.h"

#include "lang/ApplicationVisitor.h"
#include "lang/scope/LocalScope.h"
#include "lang/type/Type.h"

lang::Scope::Scope() = default;
lang::Scope::Scope(lang::Scope* containing_scope) : containing_scope_(containing_scope) {}

lang::Scope* lang::Scope::scope()
{
    assert(containing_scope_ != nullptr);
    return containing_scope_;
}

lang::Scope const* lang::Scope::scope() const
{
    assert(containing_scope_ != nullptr);
    return containing_scope_;
}

lang::GlobalScope* lang::Scope::getGlobalScope()
{
    return scope()->getGlobalScope();
}

lang::GlobalScope const* lang::Scope::getGlobalScope() const
{
    return scope()->getGlobalScope();
}

lang::OrderedScope* lang::Scope::asOrderedScope()
{
    return nullptr;
}

lang::Context& lang::Scope::context()
{
    return getGlobalScope()->context();
}

lang::Context const& lang::Scope::context() const
{
    return getGlobalScope()->context();
}

std::string lang::Scope::getTemporaryName()
{
    return "$temp" + std::to_string(temp_name_counter_++);
}

Owned<lang::OrderedScope> lang::Scope::makeLocalScope()
{
    auto local_scope = makeOwned<lang::LocalScope>(this);
    addChild(*local_scope);

    onSubScope(local_scope.get());

    return local_scope;
}

void lang::Scope::registerUsageIfUndefined(lang::ResolvingHandle<lang::Type> type)
{
    if (!type->isDefined()) { registerUsage(type); }
}

Optional<lang::OwningHandle<lang::Variable>> lang::Scope::connectWithDefinitionAccordingToOrdering(
    lang::OwningHandle<lang::Variable> variable)
{
    return variable;
}

void lang::Scope::onSubScope(lang::Scope*) {}

void lang::Scope::addDependency(lang::ResolvingHandle<lang::Variable> variable)
{
    assert(variable->isDefined());

    if (variable->scope() == this) return;

    if (!variable_to_dependency_index_.contains(variable))
    {
        variable_to_dependency_index_.emplace(variable, variable_dependencies_.size());
        variable_dependencies_.emplace_back(variable);
    }

    variable_dependencies_[variable_to_dependency_index_.at(variable)].count++;

    scope()->addDependency(variable);
}

void lang::Scope::addDependency(lang::ResolvingHandle<lang::Function> function)
{
    assert(function->isDefined());

    if (function->scope() == this) return;

    if (!function_dependencies_set_.contains(function))
    {
        function_dependencies_set_.emplace(function);
        function_dependencies_.emplace_back(function);
    }

    scope()->addDependency(function);
}

std::vector<lang::Scope::VariableDependency> lang::Scope::getVariableDependencies()
{
    return variable_dependencies_;
}

std::vector<lang::ResolvingHandle<lang::Function>> lang::Scope::getFunctionDependencies()
{
    return function_dependencies_;
}
