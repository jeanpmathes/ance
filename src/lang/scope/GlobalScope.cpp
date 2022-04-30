#include "GlobalScope.h"

#include <ostream>

#include "lang/expression/ConstantExpression.h"
#include "lang/type/IntegerType.h"
#include "lang/type/TypeAlias.h"
#include "lang/type/TypeClone.h"
#include "compiler/CompileContext.h"
#include "validation/ValidationLogger.h"
#include "lang/AccessModifier.h"
#include "lang/Assigner.h"

lang::Scope* lang::GlobalScope::scope()
{
    return this;
}

lang::GlobalScope* lang::GlobalScope::getGlobalScope()
{
    return this;
}

llvm::DIScope* lang::GlobalScope::getDebugScope(CompileContext* context)
{
    return context->unit();
}

void lang::GlobalScope::validate(ValidationLogger& validation_logger)
{
    // Validate types before everything else as they are used and checked by everything.
    bool valid = true;

    for (auto const& [name, type] : defined_types_) { valid &= type->validateDefinition(validation_logger); }

    for (auto [message, location] : errors_) { validation_logger.logError(message, location); }
    if (!valid) return;

    for (auto const& [key, function] : defined_function_groups_) { function->validate(validation_logger); }
    for (auto const& [name, variable] : global_defined_variables_) { variable->validate(validation_logger); }
}

void lang::GlobalScope::expand()
{
    for (auto const& [key, function] : defined_function_groups_) { function->expand(); }

    expanded_ = true;
}

void lang::GlobalScope::determineFlow()
{
    for (auto const& [key, function] : defined_function_groups_) { function->determineFlow(); }
}

void lang::GlobalScope::validateFlow(ValidationLogger& validation_logger)
{
    for (auto const& [key, function] : defined_function_groups_) { function->validateFlow(validation_logger); }
}

void lang::GlobalScope::defineGlobalVariable(lang::AccessModifier                access,
                                             bool                                is_constant,
                                             const std::string&                  identifier,
                                             lang::ResolvingHandle<lang::Type>   type,
                                             lang::Location                      type_location,
                                             lang::Assigner                      assigner,
                                             std::unique_ptr<ConstantExpression> initializer,
                                             lang::Location                      location)
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

    lang::OwningHandle<lang::Variable> undefined;

    if (global_undefined_variables_.find(identifier) != global_undefined_variables_.end())
    {
        undefined = std::move(global_undefined_variables_[identifier]);
        global_undefined_variables_.erase(identifier);
    }
    else
    {
        undefined = lang::OwningHandle<lang::Variable>::takeOwnership(lang::makeHandled<lang::Variable>(identifier));
    }

    undefined
        ->defineAsGlobal(type, type_location, this, access, std::move(initializer), is_final, is_constant, location);
    lang::OwningHandle<lang::Variable> defined = std::move(undefined);

    addChild(*defined);
    global_defined_variables_[identifier] = std::move(defined);
}

lang::ResolvingHandle<lang::Function> lang::GlobalScope::defineExternFunction(
    const std::string&                                   identifier,
    lang::ResolvingHandle<lang::Type>                    return_type,
    lang::Location                                       return_type_location,
    const std::vector<std::shared_ptr<lang::Parameter>>& parameters,
    lang::Location                                       location)
{
    lang::ResolvingHandle<lang::FunctionGroup> group = prepareDefinedFunctionGroup(identifier);

    lang::OwningHandle<lang::Function> undefined =
        lang::OwningHandle<lang::Function>::takeOwnership(lang::makeHandled<lang::Function>(identifier));
    undefined->defineAsExtern(this, return_type, return_type_location, parameters, location);
    lang::OwningHandle<lang::Function> defined = std::move(undefined);

    auto handle = defined.handle();
    group->addFunction(std::move(defined));
    return handle;
}

lang::ResolvingHandle<lang::Function> lang::GlobalScope::defineCustomFunction(
    const std::string&                                   identifier,
    lang::AccessModifier                                 access,
    lang::ResolvingHandle<lang::Type>                    return_type,
    lang::Location                                       return_type_location,
    const std::vector<std::shared_ptr<lang::Parameter>>& parameters,
    std::unique_ptr<lang::CodeBlock>                     code,
    lang::Location                                       declaration_location,
    lang::Location                                       definition_location)
{
    lang::ResolvingHandle<lang::FunctionGroup> group = prepareDefinedFunctionGroup(identifier);

    lang::OwningHandle<lang::Function> undefined =
        lang::OwningHandle<lang::Function>::takeOwnership(lang::makeHandled<lang::Function>(identifier));
    undefined->defineAsCustom(access,
                              return_type,
                              return_type_location,
                              parameters,
                              std::move(code),
                              this,
                              declaration_location,
                              definition_location);
    lang::OwningHandle<lang::Function> defined = std::move(undefined);

    auto handle = defined.handle();
    group->addFunction(std::move(defined));
    return handle;
}

void lang::GlobalScope::defineTypeAsOther(const std::string&                identifier,
                                          lang::ResolvingHandle<lang::Type> original,
                                          lang::Location                    definition_location,
                                          lang::Location                    original_type_location)
{
    lang::OwningHandle<lang::Type>        undefined = retrieveUndefinedType(identifier);
    std::unique_ptr<lang::TypeDefinition> cloned_definition =
        std::make_unique<lang::TypeClone>(identifier, original, definition_location, original_type_location);

    undefined->define(std::move(cloned_definition));
    lang::OwningHandle<lang::Type> defined = std::move(undefined);

    defined_types_[identifier] = std::move(defined);
    defined_types_[identifier]->setContainingScope(this);
}

void lang::GlobalScope::defineTypeAliasOther(const std::string&                identifier,
                                             lang::ResolvingHandle<lang::Type> actual,
                                             lang::Location                    definition_location,
                                             lang::Location                    actual_type_location)
{
    lang::OwningHandle<lang::Type>        undefined = retrieveUndefinedType(identifier);
    std::unique_ptr<lang::TypeDefinition> alias_definition =
        std::make_unique<lang::TypeAlias>(identifier, actual, definition_location, actual_type_location);

    undefined->define(std::move(alias_definition));
    lang::OwningHandle<lang::Type> defined = std::move(undefined);

    defined_types_[identifier] = std::move(defined);
    defined_types_[identifier]->setContainingScope(this);
}

std::optional<lang::ResolvingHandle<lang::Type>> lang::GlobalScope::getType(const std::string& string)
{
    auto it = defined_types_.find(string);

    if (it != defined_types_.end())
    {
        auto& [name, type] = *it;
        return type.handle();
    }
    else {
        return {};
    }
}

void lang::GlobalScope::addTypeRegistry(lang::TypeDefinitionRegistry* registry)
{
    type_registries_.push_back(registry);
}

void lang::GlobalScope::registerUsage(lang::ResolvingHandle<lang::Variable> variable)
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

    global_undefined_variables_[variable->identifier()] = lang::OwningHandle<lang::Variable>::takeOwnership(variable);
}

void lang::GlobalScope::registerUsage(lang::ResolvingHandle<lang::FunctionGroup> function_group)
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
        lang::OwningHandle<lang::FunctionGroup>::takeOwnership(function_group);
}

void lang::GlobalScope::registerUsage(lang::ResolvingHandle<lang::Type> type)
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

    undefined_types_[type->getName()] = lang::OwningHandle<lang::Type>::takeOwnership(type);
}

void lang::GlobalScope::registerDefinition(lang::ResolvingHandle<lang::Type> type)
{
    assert(type->isDefined());
    assert(defined_types_.find(type->getName()) == defined_types_.end());

    defined_types_[type->getName()] = lang::OwningHandle<lang::Type>::takeOwnership(type);
    type->setContainingScope(this);

    if (undefined_types_.find(type->getName()) != undefined_types_.end())
    {
        lang::OwningHandle<lang::Type> undefined = std::move(undefined_types_[type->getName()]);
        undefined_types_.erase(type->getName());

        undefined.handle().reroute(type);
    }
}

void lang::GlobalScope::resolve()
{
    if (!expanded_)
    {
        for (auto& registry : type_registries_)
        {
            registry->setDefaultContainingScope(this);
            registry->resolve();
        }
    }

    for (auto const& [key, group] : defined_function_groups_) { group->resolve(); }
}

bool lang::GlobalScope::resolveDefinition(lang::ResolvingHandle<lang::Variable> variable)
{
    if (global_defined_variables_.find(variable->identifier()) != global_defined_variables_.end())
    {
        variable.reroute(global_defined_variables_[variable->identifier()].handle());
        return true;
    }

    return false;
}

bool lang::GlobalScope::resolveDefinition(lang::ResolvingHandle<lang::FunctionGroup> function_group)
{
    if (defined_function_groups_.find(function_group->name()) != defined_function_groups_.end())
    {
        function_group.reroute(defined_function_groups_[function_group->name()].handle());
        return true;
    }

    return false;
}

bool lang::GlobalScope::resolveDefinition(lang::ResolvingHandle<lang::Type> type)
{
    if (defined_types_.find(type->getName()) != defined_types_.end())
    {
        type.reroute(defined_types_[type->getName()].handle());
        return true;
    }

    return false;
}

std::optional<lang::ResolvingHandle<lang::Function>> lang::GlobalScope::findEntry()
{
    auto c = defined_function_groups_.find("main");
    if (c == defined_function_groups_.end()) return {};

    auto& [name, group] = *c;

    std::vector<lang::ResolvingHandle<lang::Type>> arg_types;

    auto potential_function = group->resolveOverload(arg_types);
    if (potential_function.size() != 1) return {};

    lang::Function& function = *(potential_function.front());

    if (function.returnType()->isIntegerType(32, false)) return potential_function.front();
    else
        return {};
}

std::optional<lang::ResolvingHandle<lang::Function>> lang::GlobalScope::findExit()
{
    auto c = defined_function_groups_.find("exit");
    if (c == defined_function_groups_.end()) return {};

    auto& [name, group] = *c;

    std::vector<lang::ResolvingHandle<lang::Type>> arg_types;
    arg_types.push_back(lang::IntegerType::get(32, false));

    auto potential_function = group->resolveOverload(arg_types);
    if (potential_function.size() != 1) return {};

    lang::Function& function = *potential_function.front();

    if (function.returnType()->isVoidType()) return potential_function.front();
    else return {};
}

bool lang::GlobalScope::hasEntry()
{
    return findEntry().has_value();
}

bool lang::GlobalScope::hasExit()
{
    return findExit().has_value();
}

lang::ResolvingHandle<lang::Function> lang::GlobalScope::getEntry()
{
    std::optional<lang::ResolvingHandle<lang::Function>> potential_function = findEntry();
    assert(potential_function.has_value());
    return potential_function.value();
}

lang::ResolvingHandle<lang::Function> lang::GlobalScope::getExit()
{
    std::optional<lang::ResolvingHandle<lang::Function>> potential_function = findExit();
    assert(potential_function.has_value());
    return potential_function.value();
}

void lang::GlobalScope::createNativeBacking(CompileContext* context)
{
    for (auto const& [key, val] : defined_function_groups_) { val->createNativeBacking(context); }

    for (auto const& [identifier, variable] : global_defined_variables_)
    {
        variable->buildDeclaration(context);
        variable->buildDefinition(context);
    }
}

void lang::GlobalScope::buildFunctions(CompileContext* context)
{
    for (auto const& [key, group] : defined_function_groups_) { group->build(context); }
}

lang::ResolvingHandle<lang::FunctionGroup> lang::GlobalScope::prepareDefinedFunctionGroup(const std::string& name)
{
    if (defined_function_groups_.find(name) != defined_function_groups_.end())
    {
        return defined_function_groups_[name].handle();
    }

    lang::OwningHandle<lang::FunctionGroup> undefined;

    if (undefined_function_groups_.find(name) != undefined_function_groups_.end())
    {
        undefined = std::move(undefined_function_groups_[name]);
        undefined_function_groups_.erase(name);
    }
    else {
        undefined =
            lang::OwningHandle<lang::FunctionGroup>::takeOwnership(lang::makeHandled<lang::FunctionGroup>(name));
    }

    lang::ResolvingHandle<lang::FunctionGroup> defined = undefined.handle();
    defined_function_groups_[name]                     = std::move(undefined);
    addChild(*defined);

    return defined;
}

lang::OwningHandle<lang::Type> lang::GlobalScope::retrieveUndefinedType(const std::string& identifier)
{
    lang::OwningHandle<lang::Type> undefined;

    if (undefined_types_.find(identifier) != undefined_types_.end())
    {
        undefined = std::move(undefined_types_[identifier]);
        undefined_types_.erase(identifier);
    }
    else {
        undefined = lang::OwningHandle<lang::Type>::takeOwnership(lang::makeHandled<lang::Type>(identifier));
    }

    return undefined;
}

