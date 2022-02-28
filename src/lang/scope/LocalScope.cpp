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

llvm::DIScope* lang::LocalScope::getDebugScope(CompileContext* context)
{
    return parent_->getDebugScope(context);
}

lang::Scope* lang::LocalScope::scope() const
{
    return parent_;
}

std::optional<lang::ResolvingHandle<lang::Variable>> lang::LocalScope::defineAutoVariable(
    const std::string&                  identifier,
    lang::ResolvingHandle<lang::Type>   type,
    lang::Location                      type_location,
    lang::Assigner                      assigner,
    const std::shared_ptr<lang::Value>& value,
    lang::Location                      location)
{
    return defineLocalVariable(identifier, type, type_location, assigner, value, 0, location);
}

std::optional<lang::ResolvingHandle<lang::Variable>> lang::LocalScope::defineParameterVariable(
    const std::string&                  identifier,
    lang::ResolvingHandle<lang::Type>   type,
    lang::Location                      type_location,
    const std::shared_ptr<lang::Value>& value,
    unsigned                            parameter_no,
    lang::Location                      location)
{
    return defineLocalVariable(identifier,
                               type,
                               type_location,
                               lang::Assigner::UNSPECIFIED,
                               value,
                               parameter_no,
                               location);
}

void lang::LocalScope::registerUsage(lang::ResolvingHandle<lang::Variable> variable)
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

    undefined_types_[type->getName()] = lang::OwningHandle<lang::Type>::takeOwnership(type);
}

void lang::LocalScope::registerDefinition(lang::ResolvingHandle<lang::Type> type)
{
    assert(type->isDefined());

    // Types local to function not yet allowed.
}

void lang::LocalScope::resolve()
{
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

bool lang::LocalScope::resolveDefinition(lang::ResolvingHandle<lang::Variable>)
{
    return false;
}

bool lang::LocalScope::resolveDefinition(lang::ResolvingHandle<lang::FunctionGroup>)
{
    return false;
}

bool lang::LocalScope::resolveDefinition(lang::ResolvingHandle<lang::Type>)
{
    return false;
}

void lang::LocalScope::validate(ValidationLogger& validation_logger)
{
    for (auto const& [key, val] : defined_local_variables_) { val->validate(validation_logger); }
}

void lang::LocalScope::buildDeclarations(CompileContext* context)
{
    for (auto& [identifier, variable] : defined_local_variables_) { variable->buildDeclaration(context); }
}

std::optional<lang::ResolvingHandle<lang::Variable>> lang::LocalScope::defineLocalVariable(
    const std::string&                  identifier,
    lang::ResolvingHandle<lang::Type>   type,
    lang::Location                      type_location,
    lang::Assigner                      assigner,
    const std::shared_ptr<lang::Value>& value,
    unsigned                            parameter_no,
    lang::Location                      location)
{
    if (defined_local_variables_.find(identifier) == defined_local_variables_.end())
    {
        bool is_final = assigner.isFinal();

        lang::ResolvingHandle<lang::Variable> variable = lang::makeHandled<lang::Variable>(identifier);
        variable->defineAsLocal(type, type_location, this, is_final, value, parameter_no, location);

        addChild(*variable);
        defined_local_variables_[identifier] = lang::OwningHandle<lang::Variable>::takeOwnership(variable);

        return std::make_optional(variable);
    }
    else
    {
        return {};
    }
}
