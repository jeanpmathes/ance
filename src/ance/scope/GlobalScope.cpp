#include "GlobalScope.h"

#include <ostream>

#include "ance/expression/ConstantExpression.h"
#include "ance/type/IntegerType.h"
#include "ance/type/TypeAlias.h"
#include "ance/type/TypeClone.h"
#include "ance/type/VoidType.h"
#include "compiler/CompileContext.h"
#include "validation/ValidationLogger.h"

ance::Scope* ance::GlobalScope::scope()
{
    return this;
}

ance::GlobalScope* ance::GlobalScope::getGlobalScope()
{
    return this;
}

llvm::DIScope* ance::GlobalScope::getDebugScope(CompileContext* context)
{
    return context->unit();
}

void ance::GlobalScope::validate(ValidationLogger& validation_logger)
{
    // Validate types before everything else as they are used and checked by everything.
    bool valid = true;

    for (auto const& [name, type] : defined_types_) { valid &= type->validateDefinition(validation_logger); }

    for (auto [message, location] : errors_) { validation_logger.logError(message, location); }
    if (!valid) return;

    for (auto const& [key, function] : defined_function_groups_) { function->validate(validation_logger); }
    for (auto const& [name, variable] : global_defined_variables_) { variable->validate(validation_logger); }
}

void ance::GlobalScope::defineGlobalVariable(AccessModifier                    access,
                                             bool                              is_constant,
                                             const std::string&                identifier,
                                             ance::ResolvingHandle<ance::Type> type,
                                             ance::Location                    type_location,
                                             Assigner                          assigner,
                                             ConstantExpression*               initializer,
                                             ance::Location                    location)
{
    assert(assigner.hasSymbol());

    if (global_defined_variables_.find(identifier) != global_defined_variables_.end())
    {
        errors_.emplace_back("Name '" + identifier + "' already defined in the current context", location);
        return;
    }

    if (!initializer)
    {
        errors_.emplace_back("Constants require an explicit initializer", location);
        return;
    }

    bool is_final = assigner.isFinal();

    if (is_constant && !is_final)
    {
        errors_.emplace_back("Assignment to constants must be final", location);
        return;
    }

    ance::OwningHandle<ance::Variable> undefined;

    if (global_undefined_variables_.find(identifier) != global_undefined_variables_.end())
    {
        undefined = std::move(global_undefined_variables_[identifier]);
        global_undefined_variables_.erase(identifier);
    }
    else
    {
        undefined = ance::OwningHandle<ance::Variable>::takeOwnership(ance::makeHandled<ance::Variable>(identifier));
    }

    undefined->defineAsGlobal(type, type_location, this, access, initializer, is_final, is_constant, location);
    ance::OwningHandle<ance::Variable> defined = std::move(undefined);

    global_defined_variables_[identifier] = std::move(defined);
}

ance::ResolvingHandle<ance::Function> ance::GlobalScope::defineExternFunction(
    const std::string&                                   identifier,
    ance::ResolvingHandle<ance::Type>                    return_type,
    ance::Location                                       return_type_location,
    const std::vector<std::shared_ptr<ance::Parameter>>& parameters,
    ance::Location                                       location)
{
    ance::ResolvingHandle<ance::FunctionGroup> group = prepareDefinedFunctionGroup(identifier);

    ance::OwningHandle<ance::Function> undefined =
        ance::OwningHandle<ance::Function>::takeOwnership(ance::makeHandled<ance::Function>(identifier));
    undefined->defineAsExtern(this, return_type, return_type_location, parameters, location);
    ance::OwningHandle<ance::Function> defined = std::move(undefined);

    auto handle                    = defined.handle();
    group->addFunction(std::move(defined));
    return handle;
}

ance::ResolvingHandle<ance::Function> ance::GlobalScope::defineCustomFunction(
    const std::string&                                   identifier,
    AccessModifier                                       access,
    ance::ResolvingHandle<ance::Type>                    return_type,
    ance::Location                                       return_type_location,
    const std::vector<std::shared_ptr<ance::Parameter>>& parameters,
    ance::Location                                       declaration_location,
    ance::Location                                       definition_location)
{
    ance::ResolvingHandle<ance::FunctionGroup> group = prepareDefinedFunctionGroup(identifier);

    ance::OwningHandle<ance::Function> undefined =
        ance::OwningHandle<ance::Function>::takeOwnership(ance::makeHandled<ance::Function>(identifier));
    undefined->defineAsCustom(access,
                              return_type,
                              return_type_location,
                              parameters,
                              this,
                              declaration_location,
                              definition_location);
    ance::OwningHandle<ance::Function> defined = std::move(undefined);

    auto handle                    = defined.handle();
    group->addFunction(std::move(defined));
    return handle;
}

void ance::GlobalScope::defineTypeAsOther(const std::string&                identifier,
                                          ance::ResolvingHandle<ance::Type> original,
                                          ance::Location                    definition_location,
                                          ance::Location                    original_type_location)
{
    ance::OwningHandle<ance::Type>        undefined = retrieveUndefinedType(identifier);
    std::unique_ptr<ance::TypeDefinition> cloned_definition =
        std::make_unique<ance::TypeClone>(identifier, original, definition_location, original_type_location);

    undefined->define(std::move(cloned_definition));
    ance::OwningHandle<ance::Type> defined = std::move(undefined);

    defined_types_[identifier] = std::move(defined);
    defined_types_[identifier]->setContainingScope(this);
}

void ance::GlobalScope::defineTypeAliasOther(const std::string&                identifier,
                                             ance::ResolvingHandle<ance::Type> actual,
                                             ance::Location                    definition_location,
                                             ance::Location                    actual_type_location)
{
    ance::OwningHandle<ance::Type>        undefined = retrieveUndefinedType(identifier);
    std::unique_ptr<ance::TypeDefinition> alias_definition =
        std::make_unique<ance::TypeAlias>(identifier, actual, definition_location, actual_type_location);

    undefined->define(std::move(alias_definition));
    ance::OwningHandle<ance::Type> defined = std::move(undefined);

    defined_types_[identifier] = std::move(defined);
    defined_types_[identifier]->setContainingScope(this);
}

std::optional<ance::ResolvingHandle<ance::Type>> ance::GlobalScope::getType(const std::string& string)
{
    auto it = defined_types_.find(string);

    if (it != defined_types_.end())
    {
        auto& [name, type] = *it;
        return type.handle();
    }
    else
    {
        return {};
    }
}

void ance::GlobalScope::addTypeRegistry(ance::TypeDefinitionRegistry* registry)
{
    type_registries_.push_back(registry);
}

void ance::GlobalScope::registerUsage(ance::ResolvingHandle<ance::Variable> variable)
{
    assert(!variable->isDefined());

    if (global_undefined_variables_.find(variable->identifier()) != global_undefined_variables_.end())
    {
        variable.reroute(global_undefined_variables_[variable->identifier()].handle());
        return;
    }

    if (global_defined_variables_.find(variable->identifier()) != global_defined_variables_.end())
    {
        variable.reroute(global_defined_variables_[variable->identifier()].handle());
        return;
    }

    global_undefined_variables_[variable->identifier()] = ance::OwningHandle<ance::Variable>::takeOwnership(variable);
}

void ance::GlobalScope::registerUsage(ance::ResolvingHandle<ance::FunctionGroup> function_group)
{
    assert(!function_group->isDefined());

    if (undefined_function_groups_.find(function_group->name()) != undefined_function_groups_.end())
    {
        function_group.reroute(undefined_function_groups_[function_group->name()].handle());
        return;
    }

    if (defined_function_groups_.find(function_group->name()) != defined_function_groups_.end())
    {
        function_group.reroute(defined_function_groups_[function_group->name()].handle());
        return;
    }

    undefined_function_groups_[function_group->name()] =
        ance::OwningHandle<ance::FunctionGroup>::takeOwnership(function_group);
}

void ance::GlobalScope::registerUsage(ance::ResolvingHandle<ance::Type> type)
{
    assert(!type->isDefined());

    if (undefined_types_.find(type->getName()) != undefined_types_.end())
    {
        type.reroute(undefined_types_[type->getName()].handle());
        return;
    }

    if (defined_types_.find(type->getName()) != defined_types_.end())
    {
        type.reroute(defined_types_[type->getName()].handle());
        return;
    }

    undefined_types_[type->getName()] = ance::OwningHandle<ance::Type>::takeOwnership(type);
}

void ance::GlobalScope::registerDefinition(ance::ResolvingHandle<ance::Type> type)
{
    assert(type->isDefined());
    assert(defined_types_.find(type->getName()) == defined_types_.end());

    defined_types_[type->getName()] = ance::OwningHandle<ance::Type>::takeOwnership(type);
    type->setContainingScope(this);

    if (undefined_types_.find(type->getName()) != undefined_types_.end())
    {
        ance::OwningHandle<ance::Type> undefined = std::move(undefined_types_[type->getName()]);
        undefined_types_.erase(type->getName());

        undefined.handle().reroute(type);
    }
}

void ance::GlobalScope::resolve()
{
    for (auto& registry : type_registries_)
    {
        registry->setDefaultContainingScope(this);
        registry->resolve();
    }

    for (auto const& [key, group] : defined_function_groups_) { group->resolve(); }
}

bool ance::GlobalScope::resolveDefinition(ance::ResolvingHandle<ance::Variable> variable)
{
    if (global_defined_variables_.find(variable->identifier()) != global_defined_variables_.end())
    {
        variable.reroute(global_defined_variables_[variable->identifier()].handle());
        return true;
    }

    return false;
}

bool ance::GlobalScope::resolveDefinition(ance::ResolvingHandle<ance::FunctionGroup> function_group)
{
    if (defined_function_groups_.find(function_group->name()) != defined_function_groups_.end())
    {
        function_group.reroute(defined_function_groups_[function_group->name()].handle());
        return true;
    }

    return false;
}

bool ance::GlobalScope::resolveDefinition(ance::ResolvingHandle<ance::Type> type)
{
    if (defined_types_.find(type->getName()) != defined_types_.end())
    {
        type.reroute(defined_types_[type->getName()].handle());
        return true;
    }

    return false;
}

std::optional<ance::ResolvingHandle<ance::Function>> ance::GlobalScope::findEntry()
{
    auto c = defined_function_groups_.find("main");
    if (c == defined_function_groups_.end()) return {};

    auto& [name, group] = *c;

    std::vector<ance::ResolvingHandle<ance::Type>> arg_types;

    auto potential_function = group->resolveOverload(arg_types);
    if (potential_function.size() != 1) return {};

    ance::Function& function = *(potential_function.front());

    if (function.returnType()->isIntegerType(32, false)) return potential_function.front();
    else
        return {};
}

std::optional<ance::ResolvingHandle<ance::Function>> ance::GlobalScope::findExit()
{
    auto c = defined_function_groups_.find("exit");
    if (c == defined_function_groups_.end()) return {};

    auto& [name, group] = *c;

    std::vector<ance::ResolvingHandle<ance::Type>> arg_types;
    arg_types.push_back(ance::IntegerType::get(32, false));

    auto potential_function = group->resolveOverload(arg_types);
    if (potential_function.size() != 1) return {};

    ance::Function& function = *potential_function.front();

    if (function.returnType()->isVoidType()) return potential_function.front();
    else return {};
}

bool ance::GlobalScope::hasEntry()
{
    return findEntry().has_value();
}

bool ance::GlobalScope::hasExit()
{
    return findExit().has_value();
}

ance::ResolvingHandle<ance::Function> ance::GlobalScope::getEntry()
{
    std::optional<ance::ResolvingHandle<ance::Function>> potential_function = findEntry();
    assert(potential_function.has_value());
    return potential_function.value();
}

ance::ResolvingHandle<ance::Function> ance::GlobalScope::getExit()
{
    std::optional<ance::ResolvingHandle<ance::Function>> potential_function = findExit();
    assert(potential_function.has_value());
    return potential_function.value();
}

void ance::GlobalScope::createNativeBacking(CompileContext* context)
{
    for (auto const& [key, val] : defined_function_groups_) { val->createNativeBacking(context); }

    for (auto const& [identifier, variable] : global_defined_variables_)
    {
        variable->buildDeclaration(context);
        variable->buildDefinition(context);
    }
}

void ance::GlobalScope::buildFunctions(CompileContext* context)
{
    for (auto const& [key, group] : defined_function_groups_) { group->build(context); }
}

ance::ResolvingHandle<ance::FunctionGroup> ance::GlobalScope::prepareDefinedFunctionGroup(const std::string& name)
{
    if (defined_function_groups_.find(name) != defined_function_groups_.end())
    {
        return defined_function_groups_[name].handle();
    }

    ance::OwningHandle<ance::FunctionGroup> undefined;

    if (undefined_function_groups_.find(name) != undefined_function_groups_.end())
    {
        undefined = std::move(undefined_function_groups_[name]);
        undefined_function_groups_.erase(name);
    }
    else
    {
        undefined =
            ance::OwningHandle<ance::FunctionGroup>::takeOwnership(ance::makeHandled<ance::FunctionGroup>(name));
    }

    ance::ResolvingHandle<ance::FunctionGroup> defined = undefined.handle();
    defined_function_groups_[name]                     = std::move(undefined);
    return defined;
}

ance::OwningHandle<ance::Type> ance::GlobalScope::retrieveUndefinedType(const std::string& identifier)
{
    ance::OwningHandle<ance::Type> undefined;

    if (undefined_types_.find(identifier) != undefined_types_.end())
    {
        undefined = std::move(undefined_types_[identifier]);
        undefined_types_.erase(identifier);
    }
    else
    {
        undefined = ance::OwningHandle<ance::Type>::takeOwnership(ance::makeHandled<ance::Type>(identifier));
    }

    return undefined;
}
