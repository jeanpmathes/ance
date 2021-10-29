#include "Function.h"

#include <utility>

#include "ance/construct/CustomFunction.h"
#include "ance/construct/ExternFunction.h"
#include "ance/construct/LocalVariable.h"
#include "ance/scope/LocalScope.h"
#include "ance/type/VoidType.h"
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
                                    ance::Type*                                          return_type,
                                    const std::vector<std::shared_ptr<ance::Parameter>>& parameters,
                                    ance::Location                                       location)
{
    definition_ = std::make_unique<ance::ExternFunction>(this, containing_scope, return_type, parameters, location);
}

void ance::Function::defineAsCustom(AccessModifier                                       access,
                                    ance::Type*                                          return_type,
                                    const std::vector<std::shared_ptr<ance::Parameter>>& parameters,
                                    ance::Scope*                                         containing_scope,
                                    ance::Location                                       declaration_location,
                                    ance::Location                                       definition_location)
{
    definition_ = std::make_unique<ance::CustomFunction>(this,
                                                         access,
                                                         return_type,
                                                         parameters,
                                                         containing_scope,
                                                         declaration_location,
                                                         definition_location);
}

ance::Type* ance::Function::returnType() const
{
    assert(isDefined());
    return definition_->returnType();
}

ance::Type* ance::Function::parameterType(size_t index) const
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

ance::Variable* ance::Function::getVariable(std::string identifier)
{
    return definition_->getVariable(identifier);
}

bool ance::Function::isTypeRegistered(const std::string& type_name)
{
    return definition_->isTypeRegistered(type_name);
}

ance::Type* ance::Function::getType(const std::string& type_name)
{
    return definition_->getType(type_name);
}

void ance::Function::registerType(ance::Type* type)
{
    definition_->registerType(type);
}

ance::LocalScope* ance::Function::getInsideScope()
{
    return definition_->getInsideScope();
}
