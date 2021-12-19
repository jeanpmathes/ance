#include "Function.h"

#include <utility>

#include "ance/construct/CustomFunction.h"
#include "ance/construct/ExternFunction.h"
#include "ance/construct/LocalVariable.h"
#include "ance/scope/LocalScope.h"
#include "compiler/CompileContext.h"
#include "validation/ValidationLogger.h"

ance::Function::Function(std::string function_name) : name_(std::move(function_name)) {}

const std::string& ance::Function::name() const
{
    return name_;
}

bool ance::Function::isDefined() const
{
    return (definition_ != nullptr);
}

void ance::Function::defineAsExtern(ance::Scope*                                         containing_scope,
                                    ance::ResolvingHandle<ance::Type>                    return_type,
                                    ance::Location                                       return_type_location,
                                    const std::vector<std::shared_ptr<ance::Parameter>>& parameters,
                                    ance::Location                                       location)
{
    definition_ = std::make_unique<ance::ExternFunction>(this,
                                                         containing_scope,
                                                         return_type,
                                                         return_type_location,
                                                         parameters,
                                                         location);
}

void ance::Function::defineAsCustom(AccessModifier                                       access,
                                    ance::ResolvingHandle<ance::Type>                    return_type,
                                    ance::Location                                       return_type_location,
                                    const std::vector<std::shared_ptr<ance::Parameter>>& parameters,
                                    ance::Scope*                                         containing_scope,
                                    ance::Location                                       declaration_location,
                                    ance::Location                                       definition_location)
{
    definition_ = std::make_unique<ance::CustomFunction>(this,
                                                         access,
                                                         return_type,
                                                         return_type_location,
                                                         parameters,
                                                         containing_scope,
                                                         declaration_location,
                                                         definition_location);
}

ance::ResolvingHandle<ance::Type> ance::Function::returnType() const
{
    assert(isDefined());
    return definition_->returnType();
}

const ance::Signature& ance::Function::signature() const
{
    assert(isDefined());
    return definition_->signature();
}

ance::ResolvingHandle<ance::Type> ance::Function::parameterType(size_t index) const
{
    assert(isDefined());
    return definition_->parameterType(index);
}

size_t ance::Function::parameterCount() const
{
    assert(isDefined());
    return definition_->parameterCount();
}

ance::Location ance::Function::location() const
{
    assert(isDefined());
    return definition_->location();
}

void ance::Function::pushStatement(Statement* statement)
{
    definition_->pushStatement(statement);
}

void ance::Function::addReturn(const std::shared_ptr<ance::Value>& value)
{
    definition_->addReturn(value);
}

void ance::Function::validate(ValidationLogger& validation_logger)
{
    definition_->validate(validation_logger);
}

void ance::Function::createNativeBacking(CompileContext* context)
{
    definition_->createNativeBacking(context);
}

void ance::Function::build(CompileContext* context)
{
    definition_->build(context);
}

bool ance::Function::validateCall(const std::vector<std::pair<std::shared_ptr<ance::Value>, ance::Location>>& arguments,
                                  ance::Location                                                              location,
                                  ValidationLogger& validation_logger)
{
    return definition_->validateCall(arguments, location, validation_logger);
}

std::shared_ptr<ance::Value> ance::Function::buildCall(const std::vector<std::shared_ptr<ance::Value>>& arguments,
                                                       CompileContext*                                  context) const
{
    return definition_->buildCall(arguments, context);
}

ance::Scope* ance::Function::scope()
{
    return definition_->scope();
}

ance::GlobalScope* ance::Function::getGlobalScope()
{
    return definition_->getGlobalScope();
}

llvm::DIScope* ance::Function::getDebugScope(CompileContext* context)
{
    return definition_->getDebugScope(context);
}

ance::LocalScope* ance::Function::getInsideScope()
{
    return definition_->getInsideScope();
}

void ance::Function::registerUsage(ance::ResolvingHandle<ance::Variable> variable)
{
    getInsideScope()->registerUsage(variable);
}

void ance::Function::registerUsage(ance::ResolvingHandle<ance::FunctionGroup> function_group)
{
    getInsideScope()->registerUsage(function_group);
}

void ance::Function::registerUsage(ance::ResolvingHandle<ance::Type> type)
{
    getInsideScope()->registerUsage(type);
}

void ance::Function::registerDefinition(ance::ResolvingHandle<ance::Type> type)
{
    getInsideScope()->registerDefinition(type);
}

void ance::Function::resolve()
{
    ance::Scope* inside_scope = getInsideScope();
    if (inside_scope) inside_scope->resolve();
}

bool ance::Function::resolveDefinition(ance::ResolvingHandle<ance::Variable> variable)
{
    return scope()->resolveDefinition(variable);
}

bool ance::Function::resolveDefinition(ance::ResolvingHandle<ance::FunctionGroup> function_group)
{
    return scope()->resolveDefinition(function_group);
}

bool ance::Function::resolveDefinition(ance::ResolvingHandle<ance::Type> type)
{
    return scope()->resolveDefinition(type);
}
