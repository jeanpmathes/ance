#include "VariableAccess.h"

#include <utility>

#include "lang/scope/Scope.h"
#include "validation/ValidationLogger.h"

VariableAccess::VariableAccess(lang::ResolvingHandle<lang::Variable> variable, lang::Location location)
    : Expression(location)
    , variable_(std::move(variable))
{}

lang::ResolvingHandle<lang::Variable> VariableAccess::variable() const
{
    return variable_;
}

void VariableAccess::walkDefinitions()
{
    scope()->registerUsage(variable_);
}

lang::ResolvingHandle<lang::Type> VariableAccess::type()
{
    return variable_->type();
}

bool VariableAccess::isNamed()
{
    return true;
}

bool VariableAccess::validate(ValidationLogger& validation_logger)
{
    return variable_->validateGetValue(validation_logger, location());
}

bool VariableAccess::validateAssignment(const std::shared_ptr<lang::Value>& value,
                                        lang::Location                      value_location,
                                        ValidationLogger&                   validation_logger)
{
    variable_->validateSetValue(value, validation_logger, location(), value_location);
    return true;
}

void VariableAccess::doBuild(CompileContext* context)
{
    std::shared_ptr<lang::Value> value = variable_->getValue(context);
    setValue(value);
}

void VariableAccess::doAssign(std::shared_ptr<lang::Value> value, CompileContext* context)
{
    variable_->setValue(value, context);
}

VariableAccess::~VariableAccess() = default;