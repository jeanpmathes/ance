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

lang::OrderedScope const* lang::Scope::asOrderedScope() const
{
    auto* self = const_cast<lang::Scope*>(this);
    return self->asOrderedScope();
}

lang::Context& lang::Scope::context()
{
    return getGlobalScope()->context();
}

lang::Context const& lang::Scope::context() const
{
    return getGlobalScope()->context();
}

std::string lang::Scope::getTemporaryName() const
{
    assert(this);// Just to supress warnings that this method could be static.
                 // It is not static because a different naming scheme or thread-safety might be required later.

    static uint64_t temp_name_counter = 0;
    return "$temp" + std::to_string(temp_name_counter++);
}

Owned<lang::OrderedScope> lang::Scope::makeLocalScope()
{
    auto local_scope = makeOwned<lang::LocalScope>(this);
    addChild(*local_scope);

    onSubScope(local_scope.get());

    return local_scope;
}

void lang::Scope::registerUsage(lang::ResolvingHandle<lang::Variable> variable)
{
    used_variables_.emplace_back(variable);
    onRegisterUsage(variable);
}

void lang::Scope::registerUsage(lang::ResolvingHandle<lang::FunctionGroup> function)
{
    used_function_groups_.emplace_back(function);
    onRegisterUsage(function);
}

void lang::Scope::registerUsage(lang::ResolvingHandle<lang::Type> type)
{
    used_types_.emplace_back(type);
    onRegisterUsage(type);
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

void lang::Scope::postResolve()
{
    for (auto& variable : used_variables_)
    {
        if (variable->isDefined()) { addDependency(variable); }
    }

    for (auto& function_group : used_function_groups_)
    {
        if (function_group->isDefined()) { addDependency(function_group); }
    }

    for (auto& type : used_types_)
    {
        if (type->isDefined()) { addDependency(type); }
    }
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

    if (scope() != this) scope()->addDependency(function);
}

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

    if (scope() != this) scope()->addDependency(variable);
}

void lang::Scope::addDependency(lang::ResolvingHandle<lang::FunctionGroup> function)
{
    assert(function->isDefined());

    if (function->scope() == this) return;

    if (!function_group_dependencies_set_.contains(function))
    {
        function_group_dependencies_set_.emplace(function);
        function_group_dependencies_.emplace_back(function);
    }

    if (scope() != this) scope()->addDependency(function);
}

void lang::Scope::addDependency(lang::ResolvingHandle<lang::Type> type)
{
    assert(type->isDefined());

    if (type->scope() == this) return;

    if (!type_dependencies_set_.contains(type))
    {
        type_dependencies_set_.emplace(type);
        type_dependencies_.emplace_back(type);
    }

    if (scope() != this) scope()->addDependency(type);
}

std::vector<lang::Scope::VariableDependency> lang::Scope::getVariableDependencies()
{
    return variable_dependencies_;
}

std::vector<lang::ResolvingHandle<lang::Function>> lang::Scope::getFunctionDependencies()
{
    return function_dependencies_;
}

std::vector<lang::ResolvingHandle<lang::FunctionGroup>> lang::Scope::getFunctionGroupDependencies()
{
    return function_group_dependencies_;
}

std::vector<lang::ResolvingHandle<lang::Type>> lang::Scope::getTypeDependencies()
{
    return type_dependencies_;
}
