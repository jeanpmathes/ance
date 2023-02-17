#include "Function.h"

#include <utility>

#include "compiler/CompileContext.h"
#include "lang/AccessModifier.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/ExternFunction.h"
#include "lang/construct/LocalVariable.h"
#include "lang/construct/PredefinedFunction.h"
#include "lang/scope/LocalScope.h"
#include "validation/ValidationLogger.h"

lang::Function::Function(Identifier function_name) : name_(function_name) {}

lang::Identifier const& lang::Function::name() const
{
    return name_;
}

bool lang::Function::isDefined() const
{
    return definition_.hasValue();
}

void lang::Function::defineAsExtern(Scope&                                      containing_scope,
                                    lang::ResolvingHandle<lang::Type>           return_type,
                                    lang::Location                              return_type_location,
                                    std::vector<Shared<lang::Parameter>> const& parameters,
                                    lang::Location                              location)
{
    definition_ = makeOwned<lang::ExternFunction>(*this,
                                                  containing_scope,
                                                  return_type,
                                                  return_type_location,
                                                  parameters,
                                                  location);

    addChild(*definition_.value());
}

void lang::Function::defineAsCustom(lang::AccessModifier                        access,
                                    lang::ResolvingHandle<lang::Type>           return_type,
                                    lang::Location                              return_type_location,
                                    std::vector<Shared<lang::Parameter>> const& parameters,
                                    Statement&                                  block,
                                    Scope&                                      containing_scope,
                                    lang::Location                              declaration_location,
                                    lang::Location                              definition_location)
{
    definition_ = makeOwned<lang::CustomFunction>(*this,
                                                  access,
                                                  return_type,
                                                  return_type_location,
                                                  parameters,
                                                  block,
                                                  containing_scope,
                                                  declaration_location,
                                                  definition_location);

    addChild(*definition_.value());
}

lang::PredefinedFunction& lang::Function::defineAsPredefined(lang::ResolvingHandle<lang::Type>           return_type,
                                                             std::vector<Shared<lang::Parameter>> const& parameters,
                                                             lang::Scope&   containing_scope,
                                                             lang::Location location)
{

    auto definition = makeOwned<lang::PredefinedFunction>(*this, containing_scope, return_type, parameters, location);

    lang::PredefinedFunction& predefined_function = *definition;

    definition_ = std::move(definition);
    addChild(*definition_.value());

    return predefined_function;
}

void lang::Function::defineAsInit(Statement& code, lang::Scope& containing_scope)
{

    definition_ = makeOwned<lang::InitializerFunction>(*this, code, containing_scope);
    addChild(*definition_.value());
}

Optional<lang::ResolvingHandle<lang::Variable>> lang::Function::defineParameterVariable(
    Identifier const&                 name,
    lang::ResolvingHandle<lang::Type> type,
    lang::Location                    type_location,
    Shared<lang::Value>               value,
    unsigned int                      parameter_no,
    lang::Location                    location)
{
    if (defined_parameters_.contains(name)) return {};

    bool const is_final = false;// Assigner has value UNSPECIFIED, so it's not final.

    lang::ResolvingHandle<lang::Variable> variable = lang::makeHandled<lang::Variable>(name);
    variable->defineAsLocal(type, type_location, *this, is_final, value, parameter_no, location);

    addChild(*variable);
    defined_parameters_.emplace(name, lang::OwningHandle<lang::Variable>::takeOwnership(variable));

    return makeOptional(variable);
}

lang::AccessModifier lang::Function::access() const
{
    assert(isDefined());
    return definition_.value()->access();
}

lang::ResolvingHandle<lang::Type> lang::Function::returnType()
{
    assert(isDefined());
    return definition_.value()->returnType();
}

lang::Type const& lang::Function::returnType() const
{
    assert(isDefined());
    return definition_.value()->returnType();
}

lang::Signature const& lang::Function::signature() const
{
    assert(isDefined());
    return definition_.value()->signature();
}

lang::ResolvingHandle<lang::Type> lang::Function::parameterType(size_t index)
{
    assert(isDefined());
    return definition_.value()->parameterType(index);
}

lang::Type const& lang::Function::parameterType(size_t index) const
{
    assert(isDefined());
    return definition_.value()->parameterType(index);
}

size_t lang::Function::parameterCount() const
{
    assert(isDefined());
    return definition_.value()->parameterCount();
}

lang::Location lang::Function::location() const
{
    assert(isDefined());
    return definition_.value()->location();
}

bool lang::Function::isMangled() const
{
    assert(isDefined());
    return definition_.value()->isMangled();
}

bool lang::Function::isImported() const
{
    assert(isDefined());
    return definition_.value()->isImported();
}

void lang::Function::validate(ValidationLogger& validation_logger) const
{
    definition_.value()->validate(validation_logger);
}

void lang::Function::determineFlow()
{
    definition_.value()->determineFlow();
}

void lang::Function::validateFlow(ValidationLogger& validation_logger) const
{
    definition_.value()->validateFlow(validation_logger);
}

void lang::Function::createNativeBacking(CompileContext& context)
{
    definition_.value()->createNativeBacking(context);
}

void lang::Function::build(CompileContext& context)
{
    definition_.value()->build(context);
}

void lang::Function::buildDeclarations(CompileContext& context)
{
    for (auto& [name, parameter] : defined_parameters_) { parameter->buildDeclaration(context); }
}

void lang::Function::buildFinalization(CompileContext& context)
{
    for (auto& [name, parameter] : defined_parameters_) { parameter->buildFinalization(context); }
}

bool lang::Function::validateCall(
    std::vector<std::pair<std::reference_wrapper<lang::Value const>, lang::Location>> const& arguments,
    lang::Location                                                                           location,
    ValidationLogger&                                                                        validation_logger) const
{
    return definition_.value()->validateCall(arguments, location, validation_logger);
}

Optional<Shared<lang::Value>> lang::Function::buildCall(std::vector<Shared<lang::Value>> const& arguments,
                                                        CompileContext&                         context)
{
    return definition_.value()->buildCall(arguments, context);
}

lang::Scope* lang::Function::scope()
{
    return &definition_.value()->scope();
}

lang::GlobalScope* lang::Function::getGlobalScope()
{
    return definition_.value()->getGlobalScope();
}

lang::GlobalScope const* lang::Function::getGlobalScope() const
{
    return definition_.value()->getGlobalScope();
}

llvm::DIScope* lang::Function::getDebugScope(CompileContext& context) const
{
    return definition_.value()->getDebugScope(context);
}

lang::LocalScope* lang::Function::getInsideScope()
{
    return definition_.value()->getInsideScope();
}

std::vector<lang::BasicBlock*> const& lang::Function::getBasicBlocks() const
{
    return definition_.value()->getBasicBlocks();
}

void lang::Function::registerUsage(lang::ResolvingHandle<lang::Variable> variable)
{
    assert(!variable->isDefined());

    if (undefined_variables_.contains(variable->name()))
    {
        variable.reroute(undefined_variables_.at(variable->name()).handle());
        return;
    }

    if (defined_parameters_.contains(variable->name()))
    {
        variable.reroute(defined_parameters_.at(variable->name()).handle());
        return;
    }

    undefined_variables_.emplace(variable->name(), lang::OwningHandle<lang::Variable>::takeOwnership(variable));
}

void lang::Function::registerUsage(lang::ResolvingHandle<lang::FunctionGroup> function_group)
{
    assert(!function_group->isDefined());

    if (undefined_function_groups_.contains(function_group->name()))
    {
        function_group.reroute(undefined_function_groups_.at(function_group->name()).handle());
        return;
    }

    undefined_function_groups_.emplace(function_group->name(),
                                       lang::OwningHandle<lang::FunctionGroup>::takeOwnership(function_group));
}

void lang::Function::registerUsage(lang::ResolvingHandle<lang::Type> type)
{
    assert(!type->isDefined());

    if (undefined_types_.find(type->name()) != undefined_types_.end())
    {
        type.reroute(undefined_types_.at(type->name()).handle());
        return;
    }

    undefined_types_.emplace(type->name(), lang::OwningHandle<lang::Type>::takeOwnership(type));
}

void lang::Function::registerDefinition(lang::ResolvingHandle<lang::Type> type)
{
    getInsideScope()->registerDefinition(type);
}

void lang::Function::resolve()
{
    lang::Scope* inside_scope = getInsideScope();
    if (inside_scope) inside_scope->resolve();

    auto fn_it = undefined_function_groups_.begin();

    while (fn_it != undefined_function_groups_.end())
    {
        auto& [name, function_group] = *fn_it;

        if (scope()->resolveDefinition(function_group.handle())) { fn_it = undefined_function_groups_.erase(fn_it); }
        else { ++fn_it; }
    }

    auto var_it = undefined_variables_.begin();

    while (var_it != undefined_variables_.end())
    {
        auto& [name, variable] = *var_it;

        if (scope()->resolveDefinition(variable.handle())) { var_it = undefined_variables_.erase(var_it); }
        else { ++var_it; }
    }

    auto tp_it = undefined_types_.begin();

    while (tp_it != undefined_types_.end())
    {
        auto& [name, type] = *tp_it;

        if (scope()->resolveDefinition(type.handle())) { tp_it = undefined_types_.erase(tp_it); }
        else { ++tp_it; }
    }
}

void lang::Function::postResolve()
{
    definition_.value()->postResolve();
}

bool lang::Function::resolveDefinition(lang::ResolvingHandle<lang::Variable> variable)
{
    if (defined_parameters_.contains(variable->name()))
    {
        variable.reroute(defined_parameters_.at(variable->name()).handle());
        return true;
    }

    return scope()->resolveDefinition(variable);
}

bool lang::Function::resolveDefinition(lang::ResolvingHandle<lang::FunctionGroup> function_group)
{
    return scope()->resolveDefinition(function_group);
}

bool lang::Function::resolveDefinition(lang::ResolvingHandle<lang::Type> type)
{
    return scope()->resolveDefinition(type);
}
