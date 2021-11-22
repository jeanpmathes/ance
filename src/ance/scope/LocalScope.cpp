#include "LocalScope.h"

#include "ance/scope/GlobalScope.h"

ance::LocalScope::LocalScope(ance::Scope* parent) : parent_(parent) {}

ance::Scope* ance::LocalScope::scope()
{
    return parent_;
}

ance::GlobalScope* ance::LocalScope::getGlobalScope()
{
    return parent_->getGlobalScope();
}

llvm::DIScope* ance::LocalScope::getDebugScope(CompileContext* context)
{
    return parent_->getDebugScope(context);
}

ance::Scope* ance::LocalScope::scope() const
{
    return parent_;
}

std::optional<ance::ResolvingHandle<ance::Variable>> ance::LocalScope::defineAutoVariable(
    const std::string&                  identifier,
    ance::ResolvingHandle<ance::Type>   type,
    ance::Location                      type_location,
    Assigner                            assigner,
    const std::shared_ptr<ance::Value>& value,
    ance::Location                      location)
{
    return defineLocalVariable(identifier, type, type_location, assigner, value, 0, location);
}

std::optional<ance::ResolvingHandle<ance::Variable>> ance::LocalScope::defineParameterVariable(
    const std::string&                  identifier,
    ance::ResolvingHandle<ance::Type>   type,
    ance::Location                      type_location,
    Assigner                            assigner,
    const std::shared_ptr<ance::Value>& value,
    unsigned                            parameter_no,
    ance::Location                      location)
{
    return defineLocalVariable(identifier, type, type_location, assigner, value, parameter_no, location);
}

void ance::LocalScope::registerUsage(ance::ResolvingHandle<ance::Variable> variable)
{
    assert(!variable->isDefined());

    if (undefined_variables_.find(variable->identifier()) != undefined_variables_.end())
    {
        variable.reroute(undefined_variables_[variable->identifier()].handle());
        return;
    }

    if (defined_local_variables_.find(variable->identifier()) != defined_local_variables_.end())
    {
        variable.reroute(defined_local_variables_[variable->identifier()].handle());
        return;
    }

    undefined_variables_[variable->identifier()] = ance::OwningHandle<ance::Variable>::takeOwnership(variable);
}

void ance::LocalScope::registerUsage(ance::ResolvingHandle<ance::Function> function)
{
    assert(!function->isDefined());

    if (undefined_functions_.find(function->name()) != undefined_functions_.end())
    {
        function.reroute(undefined_functions_[function->name()].handle());
        return;
    }

    undefined_functions_[function->name()] = ance::OwningHandle<ance::Function>::takeOwnership(function);
}

void ance::LocalScope::registerUsage(ance::ResolvingHandle<ance::Type> type)
{
    assert(!type->isDefined());

    if (undefined_types_.find(type->getName()) != undefined_types_.end())
    {
        type.reroute(undefined_types_[type->getName()].handle());
        return;
    }

    undefined_types_[type->getName()] = ance::OwningHandle<ance::Type>::takeOwnership(type);
}

void ance::LocalScope::registerDefinition(ance::ResolvingHandle<ance::Type> type)
{
    assert(type->isDefined());

    // Types local to function not yet allowed.
}

void ance::LocalScope::resolve()
{
    auto fn_it = undefined_functions_.begin();

    while (fn_it != undefined_functions_.end())
    {
        auto& [name, function] = *fn_it;

        if (scope()->resolveDefinition(function.handle())) { fn_it = undefined_functions_.erase(fn_it); }
        else
        {
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

bool ance::LocalScope::resolveDefinition(ance::ResolvingHandle<ance::Variable>)
{
    return false;
}

bool ance::LocalScope::resolveDefinition(ance::ResolvingHandle<ance::Function>)
{
    return false;
}

bool ance::LocalScope::resolveDefinition(ance::ResolvingHandle<ance::Type>)
{
    return false;
}

void ance::LocalScope::validate(ValidationLogger& validation_logger)
{
    for (auto const& [key, val] : defined_local_variables_) { val->validate(validation_logger); }
}

void ance::LocalScope::buildDeclarations(CompileContext* context)
{
    for (auto& [identifier, variable] : defined_local_variables_) { variable->buildDeclaration(context); }
}

std::optional<ance::ResolvingHandle<ance::Variable>> ance::LocalScope::defineLocalVariable(
    const std::string&                  identifier,
    ance::ResolvingHandle<ance::Type>   type,
    ance::Location                      type_location,
    Assigner                            assigner,
    const std::shared_ptr<ance::Value>& value,
    unsigned                            parameter_no,
    ance::Location                      location)
{
    if (defined_local_variables_.find(identifier) == defined_local_variables_.end())
    {
        bool is_final = assigner.isFinal();

        ance::ResolvingHandle<ance::Variable> variable = ance::makeHandled<ance::Variable>(identifier);
        variable->defineAsLocal(type, type_location, this, is_final, value, parameter_no, location);

        defined_local_variables_[identifier] = ance::OwningHandle<ance::Variable>::takeOwnership(variable);
        return std::make_optional(variable);
    }
    else
    {
        return {};
    }
}
