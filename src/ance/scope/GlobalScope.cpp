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
    for (auto const& [name, type] : defined_types_) { type->validateDefinition(validation_logger); }

    for (auto [message, location] : errors_) { validation_logger.logError(message, location); }

    for (auto const& [key, function] : defined_functions_) { function->validate(validation_logger); }
    for (auto const& [name, variable] : global_defined_variables_) { variable->validate(validation_logger); }
}

void ance::GlobalScope::defineGlobalVariable(AccessModifier                    access,
                                             bool                              is_constant,
                                             const std::string&                identifier,
                                             ance::ResolvingHandle<ance::Type> type,
                                             Assigner                          assigner,
                                             ConstantExpression*               initializer,
                                             ance::Location                    location)
{
    assert(assigner != Assigner::REFERENCE_BINDING);

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

    undefined->defineAsGlobal(type, this, access, initializer, is_final, is_constant, location);
    ance::OwningHandle<ance::Variable> defined = std::move(undefined);

    global_defined_variables_[identifier] = std::move(defined);
}

ance::ResolvingHandle<ance::Function> ance::GlobalScope::defineExternFunction(
    const std::string&                                   identifier,
    ance::ResolvingHandle<ance::Type>                    return_type,
    const std::vector<std::shared_ptr<ance::Parameter>>& parameters,
    ance::Location                                       location)
{
    ance::OwningHandle<ance::Function> undefined = retrieveUndefinedFunction(identifier);

    undefined->defineAsExtern(this, return_type, parameters, location);
    ance::OwningHandle<ance::Function> defined = std::move(undefined);

    auto handle                    = defined.handle();
    defined_functions_[identifier] = std::move(defined);
    return handle;
}

ance::ResolvingHandle<ance::Function> ance::GlobalScope::defineCustomFunction(
    const std::string&                                   identifier,
    AccessModifier                                       access,
    ance::ResolvingHandle<ance::Type>                    return_type,
    const std::vector<std::shared_ptr<ance::Parameter>>& parameters,
    ance::Location                                       declaration_location,
    ance::Location                                       definition_location)
{
    ance::OwningHandle<ance::Function> undefined = retrieveUndefinedFunction(identifier);

    undefined->defineAsCustom(access, return_type, parameters, this, declaration_location, definition_location);
    ance::OwningHandle<ance::Function> defined = std::move(undefined);

    auto handle                    = defined.handle();
    defined_functions_[identifier] = std::move(defined);
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

void ance::GlobalScope::registerUsage(ance::ResolvingHandle<ance::Function> function)
{
    assert(!function->isDefined());

    if (undefined_functions_.find(function->name()) != undefined_functions_.end())
    {
        function.reroute(undefined_functions_[function->name()].handle());
        return;
    }

    if (defined_functions_.find(function->name()) != defined_functions_.end())
    {
        function.reroute(defined_functions_[function->name()].handle());
        return;
    }

    undefined_functions_[function->name()] = ance::OwningHandle<ance::Function>::takeOwnership(function);
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

    if (undefined_types_.find(type->getName()) != undefined_types_.end())
    {
        ance::OwningHandle<ance::Type> undefined = std::move(undefined_types_[type->getName()]);
        undefined_types_.erase(type->getName());

        undefined.handle().reroute(type);
    }
}

void ance::GlobalScope::resolve()
{
    for (auto const& [key, fn] : defined_functions_) { fn->resolve(); }
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

bool ance::GlobalScope::resolveDefinition(ance::ResolvingHandle<ance::Function> function)
{
    if (defined_functions_.find(function->name()) != defined_functions_.end())
    {
        function.reroute(defined_functions_[function->name()].handle());
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

bool ance::GlobalScope::hasEntry()
{
    auto c = defined_functions_.find("main");
    if (c == defined_functions_.end()) return false;

    ance::Function& function = *(c->second);

    return function.parameterCount() == 0 && ance::IntegerType::isIntegerType(function.returnType(), 32, false);
}

bool ance::GlobalScope::hasExit()
{
    auto c = defined_functions_.find("exit");
    if (c == defined_functions_.end()) return false;

    ance::Function& function = *(c->second);

    return function.parameterCount() == 1 && ance::IntegerType::isIntegerType(function.parameterType(0), 32, false)
        && function.returnType() == ance::VoidType::get();
}

void ance::GlobalScope::createNativeBacking(CompileContext* context)
{
    for (auto const& [key, val] : defined_functions_) { val->createNativeBacking(context); }

    for (auto const& [identifier, variable] : global_defined_variables_)
    {
        variable->buildDeclaration(context);
        variable->buildDefinition(context);
    }
}

void ance::GlobalScope::buildFunctions(CompileContext* context)
{
    for (auto const& [key, val] : defined_functions_) { val->build(context); }
}

ance::OwningHandle<ance::Function> ance::GlobalScope::retrieveUndefinedFunction(const std::string& identifier)
{
    ance::OwningHandle<ance::Function> undefined;

    if (undefined_functions_.find(identifier) != undefined_functions_.end())
    {
        undefined = std::move(undefined_functions_[identifier]);
        undefined_functions_.erase(identifier);
    }
    else
    {
        undefined = ance::OwningHandle<ance::Function>::takeOwnership(ance::makeHandled<ance::Function>(identifier));
    }

    return undefined;
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
