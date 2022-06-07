#include "LocalScope.h"

#include "lang/scope/GlobalScope.h"
#include "lang/Assigner.h"

lang::LocalScope::LocalScope(lang::Scope* parent) : parent_(parent) {}

lang::Scope* lang::LocalScope::scope()
{
    return parent_;
}

lang::GlobalScope* lang::LocalScope::getGlobalScope()
{
    return parent_->getGlobalScope();
}

lang::LocalScope* lang::LocalScope::asLocalScope()
{
    return this;
}

llvm::DIScope* lang::LocalScope::getDebugScope(CompileContext* context)
{
    return parent_->getDebugScope(context);
}

lang::Scope* lang::LocalScope::scope() const
{
    return parent_;
}

void lang::LocalScope::prepareDefinition(const std::string& identifier)
{
    blockers_.emplace(identifier);
}

lang::ResolvingHandle<lang::Variable> lang::LocalScope::defineLocalVariable(const std::string& identifier,
                                                                            lang::ResolvingHandle<lang::Type> type,
                                                                            lang::Location type_location,
                                                                            lang::Assigner assigner,
                                                                            const std::shared_ptr<lang::Value>& value,
                                                                            lang::Location location)
{
    assert(blockers_.contains(identifier));

    bool is_final = assigner.isFinal();

    lang::ResolvingHandle<lang::Variable> variable = lang::makeHandled<lang::Variable>(identifier);
    variable->defineAsLocal(type, type_location, *this, is_final, value, 0, location);

    addChild(*variable);
    defined_local_variables_[identifier].push_back(lang::OwningHandle<lang::Variable>::takeOwnership(variable));

    active_variables_.insert_or_assign(identifier, variable);

    return variable;
}

bool lang::LocalScope::drop(lang::ResolvingHandle<lang::Variable> variable)
{
    if (!variable->isDefined() || !active_variables_.contains(variable->identifier())) return false;

    active_variables_.erase(variable->identifier());

    return true;
}

bool lang::LocalScope::wasVariableDropped(lang::ResolvingHandle<lang::Variable> variable) const
{
    return !active_variables_.contains(variable->identifier())
        && defined_local_variables_.contains(variable->identifier());
}

void lang::LocalScope::registerUsage(lang::ResolvingHandle<lang::Variable> variable)
{
    assert(!variable->isDefined());

    if (undefined_variables_.find(variable->identifier()) != undefined_variables_.end())
    {
        variable.reroute(undefined_variables_[variable->identifier()].handle());
        return;
    }

    if (findExistingLocalDeclaration(variable)) return;

    if (blockers_.contains(variable->identifier()))
    {
        if (blocked_variables_.contains(variable->identifier()))
        {
            variable.reroute(blocked_variables_[variable->identifier()].handle());
        }
        else {
            blocked_variables_[variable->identifier()] = lang::OwningHandle<lang::Variable>::takeOwnership(variable);
        }

        return;
    }

    lang::LocalScope* parent = scope()->asLocalScope();
    if (parent && parent->findExistingLocalDeclaration(variable)) return;

    undefined_variables_[variable->identifier()] = lang::OwningHandle<lang::Variable>::takeOwnership(variable);
}

void lang::LocalScope::registerUsage(lang::ResolvingHandle<lang::FunctionGroup> function_group)
{
    assert(!function_group->isDefined());

    if (undefined_function_groups_.find(function_group->name()) != undefined_function_groups_.end())
    {
        function_group.reroute(undefined_function_groups_[function_group->name()].handle());
        return;
    }

    if (blockers_.contains(function_group->name()))
    {
        if (blocked_function_groups_.contains(function_group->name()))
        {
            function_group.reroute(blocked_function_groups_[function_group->name()].handle());
        }
        else {
            blocked_function_groups_[function_group->name()] =
                lang::OwningHandle<lang::FunctionGroup>::takeOwnership(function_group);
        }

        return;
    }

    undefined_function_groups_[function_group->name()] =
        lang::OwningHandle<lang::FunctionGroup>::takeOwnership(function_group);
}

void lang::LocalScope::registerUsage(lang::ResolvingHandle<lang::Type> type)
{
    assert(!type->isDefined());

    if (undefined_types_.find(type->getName()) != undefined_types_.end())
    {
        type.reroute(undefined_types_[type->getName()].handle());
        return;
    }

    if (blockers_.contains(type->getName()))
    {
        if (blocked_types_.contains(type->getName())) { type.reroute(blocked_types_[type->getName()].handle()); }
        else {
            blocked_types_[type->getName()] = lang::OwningHandle<lang::Type>::takeOwnership(type);
        }

        return;
    }

    undefined_types_[type->getName()] = lang::OwningHandle<lang::Type>::takeOwnership(type);
}

void lang::LocalScope::registerDefinition(lang::ResolvingHandle<lang::Type> type)
{
    assert(type->isDefined());

    // Types local to function not yet allowed.
}

void lang::LocalScope::resolve()
{
    for (auto& sub_scope : sub_scopes_) { sub_scope->resolve(); }

    auto fn_it = undefined_function_groups_.begin();

    while (fn_it != undefined_function_groups_.end())
    {
        auto& [name, function_group] = *fn_it;

        if (scope()->resolveDefinition(function_group.handle())) { fn_it = undefined_function_groups_.erase(fn_it); }
        else {
            ++fn_it;
        }
    }

    auto var_it = undefined_variables_.begin();

    while (var_it != undefined_variables_.end())
    {
        auto& [identifier, variable] = *var_it;

        if (scope()->resolveDefinition(variable.handle())) { var_it = undefined_variables_.erase(var_it); }
        else
        {
            ++var_it;
        }
    }

    auto tp_it = undefined_types_.begin();

    while (tp_it != undefined_types_.end())
    {
        auto& [name, type] = *tp_it;

        if (scope()->resolveDefinition(type.handle())) { tp_it = undefined_types_.erase(tp_it); }
        else
        {
            ++tp_it;
        }
    }
}

bool lang::LocalScope::resolveDefinition(lang::ResolvingHandle<lang::Variable> variable)
{
    return scope()->resolveDefinition(variable);
}

bool lang::LocalScope::resolveDefinition(lang::ResolvingHandle<lang::FunctionGroup> function_group)
{
    return scope()->resolveDefinition(function_group);
}

bool lang::LocalScope::resolveDefinition(lang::ResolvingHandle<lang::Type> type)
{
    return scope()->resolveDefinition(type);
}

bool lang::LocalScope::findExistingLocalDeclaration(lang::ResolvingHandle<lang::Variable> variable)
{
    auto it = active_variables_.find(variable->identifier());

    if (it != active_variables_.end())
    {
        variable.reroute(it->second);
        return true;
    }

    return false;
}

void lang::LocalScope::onSubScope(lang::LocalScope* sub_scope)
{
    sub_scopes_.push_back(sub_scope);
}

void lang::LocalScope::validate(ValidationLogger& validation_logger)
{
    for (auto& [identifier, variables] : defined_local_variables_)
    {
        for (auto& variable : variables) { variable->validate(validation_logger); }
    }
}

void lang::LocalScope::buildDeclarations(CompileContext* context)
{
    for (auto& [identifier, variables] : defined_local_variables_)
    {
        for (auto& variable : variables) { variable->buildDeclaration(context); }
    }

    for (auto& sub_scope : sub_scopes_) { sub_scope->buildDeclarations(context); }
}
