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
}

void lang::Function::defineAsCustom(lang::AccessModifier                                 access,
                                    lang::ResolvingHandle<lang::Type>                    return_type,
                                    lang::Location                                       return_type_location,
                                    const std::vector<std::shared_ptr<lang::Parameter>>& parameters,
                                    lang::Scope*                                         containing_scope,
                                    lang::Location                                       declaration_location,
                                    lang::Location                                       definition_location)
{
    definition_ = std::make_unique<lang::CustomFunction>(this,
                                                         access,
                                                         return_type,
                                                         return_type_location,
                                                         parameters,
                                                         containing_scope,
                                                         declaration_location,
                                                         definition_location);
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

void lang::Function::pushStatement(std::unique_ptr<Statement> statement)
{
    definition_->pushStatement(std::move(statement));
}

void lang::Function::finalizeDefinition()
{
    definition_->finalizeDefinition();
}

void lang::Function::addReturn(const std::shared_ptr<lang::Value>& value)
{
    definition_->addReturn(value);
}

void lang::Function::validate(ValidationLogger& validation_logger)
{
    definition_->validate(validation_logger);
}

void lang::Function::createNativeBacking(CompileContext* context)
{
    definition_->createNativeBacking(context);
}

void lang::Function::build(CompileContext* context)
{
    definition_->build(context);
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

void lang::Function::registerUsage(lang::ResolvingHandle<lang::Variable> variable)
{
    getInsideScope()->registerUsage(variable);
}

void lang::Function::registerUsage(lang::ResolvingHandle<lang::FunctionGroup> function_group)
{
    getInsideScope()->registerUsage(function_group);
}

void lang::Function::registerUsage(lang::ResolvingHandle<lang::Type> type)
{
    getInsideScope()->registerUsage(type);
}

void lang::Function::registerDefinition(lang::ResolvingHandle<lang::Type> type)
{
    getInsideScope()->registerDefinition(type);
}

void lang::Function::resolve()
{
    lang::Scope* inside_scope = getInsideScope();
    if (inside_scope) inside_scope->resolve();
}

bool lang::Function::resolveDefinition(lang::ResolvingHandle<lang::Variable> variable)
{
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
