#include "GlobalScope.h"

#include "compiler/CompileContext.h"
#include "lang/AccessModifier.h"
#include "lang/ApplicationVisitor.h"
#include "lang/Assigner.h"
#include "lang/construct/GlobalVariable.h"
#include "lang/expression/ConstantExpression.h"
#include "lang/type/FixedWidthIntegerType.h"
#include "lang/type/StructType.h"
#include "lang/type/TypeAlias.h"
#include "validation/ValidationLogger.h"

lang::Scope* lang::GlobalScope::scope()
{
    return this;
}

lang::GlobalScope* lang::GlobalScope::getGlobalScope()
{
    return this;
}

llvm::DIScope* lang::GlobalScope::getDebugScope(CompileContext& context) const
{
    return &context.llvmUnit();
}

void lang::GlobalScope::validate(ValidationLogger& validation_logger) const
{
    // Validate types before everything else as they are used and checked by everything.
    bool valid = true;

    for (auto& [name, type] : defined_types_) { valid &= type->validateDefinition(validation_logger); }

    for (auto const& [name, location] : duplicated_names_)
    {
        validation_logger.logError("Name '" + name + "' already defined in the current context", name.location());
    }

    if (!valid) return;

    for (auto& [key, function] : defined_function_groups_) { function->validate(validation_logger); }
    for (auto& [name, variable] : global_defined_variables_) { variable->validate(validation_logger); }

    std::vector<lang::ResolvingHandle<lang::Variable>> global_variables;
    for (auto& [name, variable] : const_cast<GlobalScope*>(this)->global_defined_variables_)
    {
        global_variables.emplace_back(variable.handle());
    }

    global_variables_ = lang::GlobalVariable::determineOrder(global_variables, validation_logger);
}

void lang::GlobalScope::expand()
{
    for (auto& registry : type_registries_) { registry->clear(); }

    for (auto& [name, type] : defined_types_) { type->expand(); }

    for (auto& [name, function] : defined_function_groups_) { function->expand(); }
    for (auto& [name, variable] : global_defined_variables_) { variable->expand(); }

    expanded_ = true;
}

void lang::GlobalScope::determineFlow()
{
    for (auto& [key, function] : defined_function_groups_) { function->determineFlow(); }
    for (auto& [name, variable] : global_defined_variables_) { variable->determineFlow(); }
}

void lang::GlobalScope::validateFlow(ValidationLogger& validation_logger) const
{
    for (auto& [key, function] : defined_function_groups_) { function->validateFlow(validation_logger); }
    for (auto& [name, variable] : global_defined_variables_) { variable->validateFlow(validation_logger); }
}

void lang::GlobalScope::defineGlobalVariable(lang::AccessModifier                        access,
                                             bool                                        is_constant,
                                             lang::Identifier                            name,
                                             Optional<lang::ResolvingHandle<lang::Type>> type,
                                             lang::Location                              type_location,
                                             lang::Assigner                              assigner,
                                             Optional<Owned<Expression>>                 initializer,
                                             lang::Location                              location)
{
    if (defined_names_.contains(name))
    {
        duplicated_names_.emplace_back(name, location);
        return;
    }

    defined_names_.emplace(name);

    bool const is_final = assigner.isFinal();

    Optional<lang::OwningHandle<lang::Variable>> undefined;

    if (global_undefined_variables_.contains(name))
    {
        undefined = std::move(global_undefined_variables_.at(name));
        global_undefined_variables_.erase(name);
    }
    else { undefined = lang::OwningHandle<lang::Variable>::takeOwnership(lang::makeHandled<lang::Variable>(name)); }

    undefined.value()
        ->defineAsGlobal(type, type_location, *this, access, std::move(initializer), is_final, is_constant, location);
    lang::OwningHandle<lang::Variable> defined = std::move(undefined.value());

    addChild(*defined);
    global_defined_variables_.emplace(name, std::move(defined));
}

void lang::GlobalScope::defineExternFunction(Identifier                                  name,
                                             lang::ResolvingHandle<lang::Type>           return_type,
                                             lang::Location                              return_type_location,
                                             std::vector<Shared<lang::Parameter>> const& parameters,
                                             lang::Location                              location)
{
    if (defined_names_.contains(name) && !defined_function_groups_.contains(name))
    {
        duplicated_names_.emplace_back(name, location);
        return;
    }

    defined_names_.emplace(name);

    lang::ResolvingHandle<lang::FunctionGroup> group = prepareDefinedFunctionGroup(name);

    lang::OwningHandle<lang::Function> undefined =
        lang::OwningHandle<lang::Function>::takeOwnership(lang::makeHandled<lang::Function>(name));
    undefined->defineAsExtern(*this, return_type, return_type_location, parameters, location);
    lang::OwningHandle<lang::Function> defined = std::move(undefined);

    group->addFunction(std::move(defined));
}

void lang::GlobalScope::defineCustomFunction(Identifier                                  name,
                                             lang::AccessModifier                        access,
                                             lang::ResolvingHandle<lang::Type>           return_type,
                                             lang::Location                              return_type_location,
                                             std::vector<Shared<lang::Parameter>> const& parameters,
                                             Owned<lang::CodeBlock>                      code,
                                             lang::Location                              declaration_location,
                                             lang::Location                              definition_location)
{
    if (defined_names_.contains(name) && !defined_function_groups_.contains(name))
    {
        duplicated_names_.emplace_back(name, definition_location);
        return;
    }

    defined_names_.emplace(name);

    lang::ResolvingHandle<lang::FunctionGroup> group = prepareDefinedFunctionGroup(name);

    lang::OwningHandle<lang::Function> undefined =
        lang::OwningHandle<lang::Function>::takeOwnership(lang::makeHandled<lang::Function>(name));
    undefined->defineAsCustom(access,
                              return_type,
                              return_type_location,
                              parameters,
                              std::move(code),
                              *this,
                              declaration_location,
                              definition_location);
    lang::OwningHandle<lang::Function> defined = std::move(undefined);

    group->addFunction(std::move(defined));
}

void lang::GlobalScope::defineTypeAliasOther(Identifier                        name,
                                             lang::ResolvingHandle<lang::Type> actual,
                                             lang::Location                    definition_location,
                                             lang::Location                    actual_type_location)
{
    if (defined_names_.contains(name))
    {
        duplicated_names_.emplace_back(name, definition_location);
        return;
    }

    defined_names_.emplace(name);

    lang::OwningHandle<lang::Type> undefined = retrieveUndefinedType(name);
    Owned<lang::TypeDefinition>    alias_definition =
        makeOwned<lang::TypeAlias>(name, actual, definition_location, actual_type_location);

    undefined->define(std::move(alias_definition));
    lang::OwningHandle<lang::Type> defined = std::move(undefined);

    defined_types_.emplace(name, std::move(defined));
}

void lang::GlobalScope::defineStruct(lang::AccessModifier             access,
                                     lang::Identifier                 name,
                                     std::vector<Owned<lang::Member>> members,
                                     lang::Location                   definition_location)
{
    if (defined_names_.contains(name))
    {
        duplicated_names_.emplace_back(name, definition_location);
        return;
    }

    defined_names_.emplace(name);

    lang::OwningHandle<lang::Type> undefined = retrieveUndefinedType(name);
    Owned<lang::TypeDefinition>    struct_definition =
        makeOwned<lang::StructType>(access, name, std::move(members), definition_location);

    undefined->define(std::move(struct_definition));
    lang::OwningHandle<lang::Type> defined = std::move(undefined);

    defined_types_.emplace(name, std::move(defined));
}

Optional<lang::ResolvingHandle<lang::Type>> lang::GlobalScope::getType(Identifier string)
{
    auto it = defined_types_.find(string);

    if (it != defined_types_.end())
    {
        auto& [name, type] = *it;
        return type.handle();
    }
    else { return {}; }
}

void lang::GlobalScope::addTypeRegistry(lang::TypeDefinitionRegistry* registry)
{
    type_registries_.push_back(registry);
}

void lang::GlobalScope::registerUsage(lang::ResolvingHandle<lang::Variable> variable)
{
    assert(!variable->isDefined());

    if (global_undefined_variables_.find(variable->name()) != global_undefined_variables_.end())
    {
        variable.reroute(global_undefined_variables_.at(variable->name()).handle());
        return;
    }

    if (global_defined_variables_.find(variable->name()) != global_defined_variables_.end())
    {
        variable.reroute(global_defined_variables_.at(variable->name()).handle());
        return;
    }

    global_undefined_variables_.at(variable->name()) = lang::OwningHandle<lang::Variable>::takeOwnership(variable);
}

void lang::GlobalScope::registerUsage(lang::ResolvingHandle<lang::FunctionGroup> function_group)
{
    assert(!function_group->isDefined());

    if (undefined_function_groups_.find(function_group->name()) != undefined_function_groups_.end())
    {
        function_group.reroute(undefined_function_groups_.at(function_group->name()).handle());
        return;
    }

    if (defined_function_groups_.find(function_group->name()) != defined_function_groups_.end())
    {
        function_group.reroute(defined_function_groups_.at(function_group->name()).handle());
        return;
    }

    undefined_function_groups_.at(function_group->name()) =
        lang::OwningHandle<lang::FunctionGroup>::takeOwnership(function_group);
}

void lang::GlobalScope::registerUsage(lang::ResolvingHandle<lang::Type> type)
{
    assert(!type->isDefined());

    if (undefined_types_.contains(type->name()))
    {
        type.reroute(undefined_types_.at(type->name()).handle());
        return;
    }

    if (defined_types_.contains(type->name()))
    {
        type.reroute(defined_types_.at(type->name()).handle());
        return;
    }

    undefined_types_.emplace(type->name(), lang::OwningHandle<lang::Type>::takeOwnership(type));
}

void lang::GlobalScope::registerDefinition(lang::ResolvingHandle<lang::Type> type)
{
    assert(type->isDefined());
    assert(not defined_types_.contains(type->name()));

    defined_types_.emplace(type->name(), lang::OwningHandle<lang::Type>::takeOwnership(type));
    type->setContainingScope(this);

    if (undefined_types_.contains(type->name()))
    {
        lang::OwningHandle<lang::Type> undefined = std::move(undefined_types_.at(type->name()));
        undefined_types_.erase(type->name());

        undefined.handle().reroute(type);
    }
}

void lang::GlobalScope::resolve()
{
    for (auto& [key, group] : defined_function_groups_) { group->resolve(); }
    for (auto& [key, variable] : global_defined_variables_) { variable->resolve(); }

    for (auto& [key, type] : defined_types_) { type->setContainingScope(this); }

    // Type registries are currently incorrect, as they resolve type dependencies in an incorrect scope.

    for (auto& registry : type_registries_)
    {
        registry->setDefaultContainingScope(this);
        registry->resolve();
    }
}

void lang::GlobalScope::postResolve()
{
    if (!expanded_)
    {// Ugly, not necessary with full expansion.
        for (auto& [name, type] : defined_types_) { type->postResolve(); }
    }

    for (auto& registry : type_registries_) { registry->postResolve(); }
    for (auto& [key, group] : defined_function_groups_) { group->postResolve(); }
    for (auto& [key, variable] : global_defined_variables_) { variable->postResolve(); }
}

bool lang::GlobalScope::resolveDefinition(lang::ResolvingHandle<lang::Variable> variable)
{
    if (global_defined_variables_.find(variable->name()) != global_defined_variables_.end())
    {
        variable.reroute(global_defined_variables_.at(variable->name()).handle());
        return true;
    }

    return false;
}

bool lang::GlobalScope::resolveDefinition(lang::ResolvingHandle<lang::FunctionGroup> function_group)
{
    if (defined_function_groups_.find(function_group->name()) != defined_function_groups_.end())
    {
        function_group.reroute(defined_function_groups_.at(function_group->name()).handle());
        return true;
    }

    return false;
}

bool lang::GlobalScope::resolveDefinition(lang::ResolvingHandle<lang::Type> type)
{
    if (defined_types_.contains(type->name()))
    {
        type.reroute(defined_types_.at(type->name()).handle());
        return true;
    }

    return false;
}

Optional<lang::ResolvingHandle<lang::Function>> lang::GlobalScope::findEntry()
{
    auto c = defined_function_groups_.find(lang::Identifier::like("main"));
    if (c == defined_function_groups_.end()) return {};

    auto& [name, group] = *c;

    auto potential_function = group->resolveOverload({});
    if (potential_function.size() != 1) return {};

    lang::Function const& function = *(potential_function.front());

    if (function.returnType().isFixedWidthIntegerType(32, false)) return potential_function.front();
    else return {};
}

Optional<lang::ResolvingHandle<lang::Function>> lang::GlobalScope::findExit()
{
    auto c = defined_function_groups_.find(lang::Identifier::like("exit"));
    if (c == defined_function_groups_.end()) return {};

    auto& [name, group] = *c;

    auto input_arg_type = lang::FixedWidthIntegerType::get(32, false);

    std::vector<std::reference_wrapper<lang::Type const>> arg_types;
    arg_types.emplace_back(input_arg_type);

    auto potential_function = group->resolveOverload(arg_types);
    if (potential_function.size() != 1) return {};

    lang::Function const& function = *potential_function.front();

    if (function.returnType().isVoidType()) return potential_function.front();
    else return {};
}

bool lang::GlobalScope::hasEntry() const
{
    // The findEntry function is non-const because it returns a non-const handle, but it doesn't modify this object.
    return const_cast<GlobalScope*>(this)->findEntry().hasValue();
}

bool lang::GlobalScope::hasExit() const
{
    // The findExit function is non-const because it returns a non-const handle, but it doesn't modify this object.
    return const_cast<GlobalScope*>(this)->findExit().hasValue();
}

lang::ResolvingHandle<lang::Function> lang::GlobalScope::getEntry()
{
    Optional<lang::ResolvingHandle<lang::Function>> potential_function = findEntry();
    assert(potential_function.hasValue());
    return potential_function.value();
}

lang::ResolvingHandle<lang::Function> lang::GlobalScope::getExit()
{
    Optional<lang::ResolvingHandle<lang::Function>> potential_function = findExit();
    assert(potential_function.hasValue());
    return potential_function.value();
}

void lang::GlobalScope::createNativeBacking(CompileContext& context)
{
    for (auto& [key, val] : defined_function_groups_) { val->createNativeBacking(context); }
    for (auto& [key, val] : global_defined_variables_) { val->createNativeBacking(context); }

    for (auto& [name, variable] : global_defined_variables_) { variable->buildDeclaration(context); }

    for (auto& [name, type] : defined_types_) { type->buildNativeDeclaration(context); }
    for (auto& registry : type_registries_) { registry->buildNativeDeclarations(context); }

    for (auto& [name, type] : defined_types_) { type->buildNativeDefinition(context); }
    for (auto& registry : type_registries_) { registry->buildNativeDefinitions(context); }
}

void lang::GlobalScope::buildFunctions(CompileContext& context)
{
    for (auto& [key, group] : defined_function_groups_) { group->build(context); }
    for (auto& [key, variable] : global_defined_variables_) { variable->build(context); }
}

void lang::GlobalScope::buildInitialization(CompileContext& context)
{
    for (auto& variable : global_variables_) { variable->buildDefinition(context); }
}

void lang::GlobalScope::buildFinalization(CompileContext& context)
{
    for (auto& [name, variable] : global_defined_variables_) { variable->buildFinalization(context); }
}

lang::ResolvingHandle<lang::FunctionGroup> lang::GlobalScope::prepareDefinedFunctionGroup(Identifier name)
{
    if (defined_function_groups_.find(name) != defined_function_groups_.end())
    {
        return defined_function_groups_.at(name).handle();
    }

    Optional<lang::OwningHandle<lang::FunctionGroup>> undefined;

    if (undefined_function_groups_.contains(name))
    {
        undefined = std::move(undefined_function_groups_.at(name));
        undefined_function_groups_.erase(name);
    }
    else
    {
        undefined =
            lang::OwningHandle<lang::FunctionGroup>::takeOwnership(lang::makeHandled<lang::FunctionGroup>(name));
    }

    lang::ResolvingHandle<lang::FunctionGroup> defined = undefined->handle();
    defined_function_groups_.emplace(name, std::move(undefined.value()));
    addChild(*defined);

    return defined;
}

lang::OwningHandle<lang::Type> lang::GlobalScope::retrieveUndefinedType(Identifier name)
{
    Optional<lang::OwningHandle<lang::Type>> undefined;

    if (undefined_types_.find(name) != undefined_types_.end())
    {
        undefined = std::move(undefined_types_.at(name));
        undefined_types_.erase(name);
    }
    else { undefined = lang::OwningHandle<lang::Type>::takeOwnership(lang::makeHandled<lang::Type>(name)); }

    return std::move(undefined.value());
}
