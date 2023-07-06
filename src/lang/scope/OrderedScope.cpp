#include "OrderedScope.h"

#include "lang/ApplicationVisitor.h"

lang::OrderedScope* lang::OrderedScope::asOrderedScope()
{
    return this;
}

bool lang::OrderedScope::isNameConflicted(lang::Identifier const& name) const
{
    return scope()->isNameConflicted(name);// Redefinition allowed, so no conflict.
}

void lang::OrderedScope::addDescription(Owned<lang::Description> description)
{
    descriptions_[description->name()].emplace_back(std::move(description));
}

void lang::OrderedScope::addFunction(lang::OwningHandle<lang::Function> function)
{
    defined_functions_[function->name()].emplace_back(std::move(function));
}

void lang::OrderedScope::addVariable(lang::OwningHandle<lang::Variable> variable)
{
    assert(blockers_.contains(variable->name()));

    active_variables_.insert_or_assign(variable->name(), variable.handle());
    defined_variables_[variable->name()].emplace_back(std::move(variable));
}

void lang::OrderedScope::addType(lang::OwningHandle<lang::Type> type)
{
    defined_types_[type->name()].emplace_back(std::move(type));
}

void lang::OrderedScope::prepareDefinition(lang::Identifier name)
{
    blockers_.emplace(name);
}

bool lang::OrderedScope::drop(lang::ResolvingHandle<lang::Variable> variable)
{
    if (!variable->isDefined() || !active_variables_.contains(variable->name())) return false;

    active_variables_.erase(variable->name());

    return true;
}

bool lang::OrderedScope::wasVariableDropped(lang::Variable const& variable) const
{
    return !active_variables_.contains(variable.name()) && defined_variables_.contains(variable.name());
}

void lang::OrderedScope::onRegisterUsage(lang::ResolvingHandle<lang::Variable> variable)
{
    assert(!variable->isDefined());

    if (undefined_variables_.contains(variable->name()))
    {
        variable.reroute(undefined_variables_.at(variable->name()).handle());
        return;
    }

    lang::Scope*                           current        = this;
    Optional<OwningHandle<lang::Variable>> owned_variable = lang::OwningHandle<lang::Variable>::takeOwnership(variable);

    while (current != current->scope())
    {
        owned_variable = current->connectWithDefinitionAccordingToOrdering(std::move(owned_variable.value()));
        if (!owned_variable.hasValue()) return;
        current = current->scope();
    }

    undefined_variables_.emplace(variable->name(), std::move(owned_variable.value()));
}

void lang::OrderedScope::onRegisterUsage(lang::ResolvingHandle<lang::FunctionGroup> function_group)
{
    assert(!function_group->isDefined());

    if (undefined_function_groups_.find(function_group->name()) != undefined_function_groups_.end())
    {
        function_group.reroute(undefined_function_groups_.at(function_group->name()).handle());
        return;
    }

    if (blockers_.contains(function_group->name()))
    {
        if (blocked_function_groups_.contains(function_group->name()))
        {
            function_group.reroute(blocked_function_groups_.at(function_group->name()).handle());
        }
        else
        {
            blocked_function_groups_.at(function_group->name()) =
                lang::OwningHandle<lang::FunctionGroup>::takeOwnership(function_group);
        }

        return;
    }

    undefined_function_groups_.emplace(function_group->name(),
                                       lang::OwningHandle<lang::FunctionGroup>::takeOwnership(function_group));
}

void lang::OrderedScope::onRegisterUsage(lang::ResolvingHandle<lang::Type> type)
{
    assert(!type->isDefined());

    if (undefined_types_.contains(type->name()))
    {
        type.reroute(undefined_types_.at(type->name()).handle());
        return;
    }

    if (blockers_.contains(type->name()))
    {
        if (blocked_types_.contains(type->name())) { type.reroute(blocked_types_.at(type->name()).handle()); }
        else { blocked_types_.emplace(type->name(), lang::OwningHandle<lang::Type>::takeOwnership(type)); }

        return;
    }

    undefined_types_.emplace(type->name(), lang::OwningHandle<lang::Type>::takeOwnership(type));
}

void lang::OrderedScope::registerDefinition(lang::ResolvingHandle<lang::Type> type)
{
    assert(type->isDefined());
    // Not yet supported.
}

Optional<lang::OwningHandle<lang::Variable>> lang::OrderedScope::connectWithDefinitionAccordingToOrdering(
    lang::OwningHandle<lang::Variable> variable)
{
    auto it = active_variables_.find(variable->name());

    if (it != active_variables_.end())
    {
        variable.handle().reroute(it->second);
        return std::nullopt;
    }

    if (blockers_.contains(variable->name()))
    {
        if (blocked_variables_.contains(variable->name()))
        {
            variable.handle().reroute(blocked_variables_.at(variable->name()).handle());
        }
        else { blocked_variables_.emplace(variable->name(), std::move(variable)); }

        return std::nullopt;
    }

    return variable;
}

template<typename E>
static void resolveEntities(lang::Scope& scope, std::map<lang::Identifier, E>& entities)
{
    auto it = entities.begin();

    while (it != entities.end())
    {
        auto& [name, entity] = *it;

        if (scope.resolveDefinition(entity.handle())) { it = entities.erase(it); }
        else { ++it; }
    }
}

void lang::OrderedScope::resolve()
{
    for (auto& sub_scope : sub_scopes_) { sub_scope->resolve(); }

    lang::Scope& parent = *scope();

    resolveEntities(parent, undefined_function_groups_);
    resolveEntities(parent, undefined_variables_);
    resolveEntities(parent, undefined_types_);
}

void lang::OrderedScope::postResolve()
{
    // Nothing to do.

    Scope::postResolve();
}

bool lang::OrderedScope::resolveDefinition(lang::ResolvingHandle<lang::Variable> variable)
{
    // If the variable were defined in this scope, we would have found it when registering the usage.
    return scope()->resolveDefinition(variable);
}

bool lang::OrderedScope::resolveDefinition(lang::ResolvingHandle<lang::FunctionGroup> function_group)
{
    // If the variable were defined in this scope, we would have found it when registering the usage.
    return scope()->resolveDefinition(function_group);
}

bool lang::OrderedScope::resolveDefinition(lang::ResolvingHandle<lang::Type> type)
{
    // If the variable were defined in this scope, we would have found it when registering the usage.
    return scope()->resolveDefinition(type);
}

void lang::OrderedScope::buildDeclarations(CompileContext& context)
{
    for (auto& [name, variables] : defined_variables_)
    {
        for (auto& variable : variables) { variable->buildDeclaration(context); }
    }
    for (auto& sub_scope : sub_scopes_)
    {
        if (auto ordered_sub_scope = sub_scope->asOrderedScope()) ordered_sub_scope->buildDeclarations(context);
    }
}

void lang::OrderedScope::buildFinalization(CompileContext& context)
{
    for (auto& [name, variable] : active_variables_) { variable->buildFinalization(context); }
}

void lang::OrderedScope::onSubScope(lang::Scope* sub_scope)
{
    sub_scopes_.emplace_back(sub_scope);
}
