#include "Function.h"

#include <utility>

#include "lang/construct/CustomFunction.h"
#include "lang/construct/ExternFunction.h"
#include "lang/construct/LocalVariable.h"
#include "lang/scope/LocalScope.h"
#include "compiler/CompileContext.h"
#include "validation/ValidationLogger.h"
#include "lang/AccessModifier.h"
#include "lang/statement/Statement.h"

lang::Function::Function(std::string function_name) : name_(std::move(function_name)) {}

const std::string& lang::Function::name() const
{
    return name_;
}

bool lang::Function::isDefined() const
{
    return (definition_ != nullptr);
}

void lang::Function::defineAsExtern(lang::Scope*                                         containing_scope,
                                    lang::ResolvingHandle<lang::Type>                    return_type,
                                    lang::Location                                       return_type_location,
                                    const std::vector<std::shared_ptr<lang::Parameter>>& parameters,
                                    lang::Location                                       location)
{
    definition_ = std::make_unique<lang::ExternFunction>(this,
                                                         containing_scope,
                                                         return_type,
                                                         return_type_location,
                                                         parameters,
                                                         location);

    addChild(*definition_);
}

void lang::Function::defineAsCustom(lang::AccessModifier                                 access,
                                    lang::ResolvingHandle<lang::Type>                    return_type,
                                    lang::Location                                       return_type_location,
                                    const std::vector<std::shared_ptr<lang::Parameter>>& parameters,
                                    std::unique_ptr<lang::CodeBlock>                     block,
                                    lang::Scope*                                         containing_scope,
                                    lang::Location                                       declaration_location,
                                    lang::Location                                       definition_location)
{
    definition_ = std::make_unique<lang::CustomFunction>(this,
                                                         access,
                                                         return_type,
                                                         return_type_location,
                                                         parameters,
                                                         std::move(block),
                                                         containing_scope,
                                                         declaration_location,
                                                         definition_location);

    addChild(*definition_);
}

std::optional<lang::ResolvingHandle<lang::Variable>> lang::Function::defineParameterVariable(
    const std::string&                  identifier,
    lang::ResolvingHandle<lang::Type>   type,
    lang::Location                      type_location,
    const std::shared_ptr<lang::Value>& value,
    unsigned int                        parameter_no,
    lang::Location                      location)
{
    if (defined_parameters_.find(identifier) == defined_parameters_.end())
    {
        bool is_final = false;// Assigner has value UNSPECIFIED, so it's not final.

        lang::ResolvingHandle<lang::Variable> variable = lang::makeHandled<lang::Variable>(identifier);
        variable->defineAsLocal(type, type_location, this, is_final, value, parameter_no, location);

        addChild(*variable);
        defined_parameters_[identifier] = lang::OwningHandle<lang::Variable>::takeOwnership(variable);

        return std::make_optional(variable);
    }
    else {
        return {};
    }
}

lang::ResolvingHandle<lang::Type> lang::Function::returnType() const
{
    assert(isDefined());
    return definition_->returnType();
}

const lang::Signature& lang::Function::signature() const
{
    assert(isDefined());
    return definition_->signature();
}

lang::ResolvingHandle<lang::Type> lang::Function::parameterType(size_t index) const
{
    assert(isDefined());
    return definition_->parameterType(index);
}

size_t lang::Function::parameterCount() const
{
    assert(isDefined());
    return definition_->parameterCount();
}

lang::Location lang::Function::location() const
{
    assert(isDefined());
    return definition_->location();
}

bool lang::Function::isMangled() const
{
    assert(isDefined());
    return definition_->isMangled();
}

void lang::Function::validate(ValidationLogger& validation_logger)
{
    definition_->validate(validation_logger);
}

void lang::Function::expand()
{
    {// Quick fix to remove old scope from children, with full expansion this would be unnecessary.
        clearChildren();
        addChild(*definition_);
        for (const auto& [name, parameter] : defined_parameters_) { addChild(*parameter); }
    }

    definition_->expand();
}

void lang::Function::determineFlow()
{
    definition_->determineFlow();
}

void lang::Function::validateFlow(ValidationLogger& validation_logger)
{
    definition_->validateFlow(validation_logger);
}

void lang::Function::createNativeBacking(CompileContext* context)
{
    definition_->createNativeBacking(context);
}

void lang::Function::build(CompileContext* context)
{
    definition_->build(context);
}

void lang::Function::buildDeclarations(CompileContext* context)
{
    for (auto& [identifier, parameter] : defined_parameters_) { parameter->buildDeclaration(context); }
}

bool lang::Function::validateCall(const std::vector<std::pair<std::shared_ptr<lang::Value>, lang::Location>>& arguments,
                                  lang::Location                                                              location,
                                  ValidationLogger& validation_logger)
{
    return definition_->validateCall(arguments, location, validation_logger);
}

std::shared_ptr<lang::Value> lang::Function::buildCall(const std::vector<std::shared_ptr<lang::Value>>& arguments,
                                                       CompileContext*                                  context) const
{
    return definition_->buildCall(arguments, context);
}

lang::Scope* lang::Function::scope()
{
    return definition_->scope();
}

lang::GlobalScope* lang::Function::getGlobalScope()
{
    return definition_->getGlobalScope();
}

llvm::DIScope* lang::Function::getDebugScope(CompileContext* context)
{
    return definition_->getDebugScope(context);
}

lang::LocalScope* lang::Function::getInsideScope()
{
    return definition_->getInsideScope();
}

const std::vector<lang::BasicBlock*>& lang::Function::getBasicBlocks() const
{
    return definition_->getBasicBlocks();
}

void lang::Function::registerUsage(lang::ResolvingHandle<lang::Variable> variable)
{
    assert(!variable->isDefined());

    if (undefined_variables_.find(variable->identifier()) != undefined_variables_.end())
    {
        variable.reroute(undefined_variables_[variable->identifier()].handle());
        return;
    }

    if (defined_parameters_.find(variable->identifier()) != defined_parameters_.end())
    {
        variable.reroute(defined_parameters_[variable->identifier()].handle());
        return;
    }

    undefined_variables_[variable->identifier()] = lang::OwningHandle<lang::Variable>::takeOwnership(variable);
}

void lang::Function::registerUsage(lang::ResolvingHandle<lang::FunctionGroup> function_group)
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

void lang::Function::registerUsage(lang::ResolvingHandle<lang::Type> type)
{
    assert(!type->isDefined());

    if (undefined_types_.find(type->getName()) != undefined_types_.end())
    {
        type.reroute(undefined_types_[type->getName()].handle());
        return;
    }

    undefined_types_[type->getName()] = lang::OwningHandle<lang::Type>::takeOwnership(type);
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
        else {
            ++fn_it;
        }
    }

    auto var_it = undefined_variables_.begin();

    while (var_it != undefined_variables_.end())
    {
        auto& [identifier, variable] = *var_it;

        if (scope()->resolveDefinition(variable.handle())) { var_it = undefined_variables_.erase(var_it); }
        else {
            ++var_it;
        }
    }

    auto tp_it = undefined_types_.begin();

    while (tp_it != undefined_types_.end())
    {
        auto& [name, type] = *tp_it;

        if (scope()->resolveDefinition(type.handle())) { tp_it = undefined_types_.erase(tp_it); }
        else {
            ++tp_it;
        }
    }
}

bool lang::Function::resolveDefinition(lang::ResolvingHandle<lang::Variable> variable)
{
    if (defined_parameters_.find(variable->identifier()) != defined_parameters_.end())
    {
        variable.reroute(defined_parameters_[variable->identifier()].handle());
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

