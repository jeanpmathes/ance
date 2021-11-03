#include "VariableAccess.h"

#include <utility>

#include "ance/scope/Scope.h"
#include "validation/ValidationLogger.h"

VariableAccess::VariableAccess(ance::ResolvingHandle<ance::Variable> variable, ance::Location location)
    : Expression(location)
    , variable_(std::move(variable))
{}

void VariableAccess::setScope(ance::Scope* scope)
{
    scope->registerUsage(variable_);
}

ance::Type* VariableAccess::type()
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

bool VariableAccess::validateAssignment(const std::shared_ptr<ance::Value>& value,
                                        ance::Location                      value_location,
                                        ValidationLogger&                   validation_logger)
{
    variable_->validateSetValue(value, validation_logger, location(), value_location);
    return true;
}

void VariableAccess::doBuild(CompileContext* context)
{
    std::shared_ptr<ance::Value> value = variable_->getValue(context);
    setValue(value);
}

void VariableAccess::doAssign(std::shared_ptr<ance::Value> value, CompileContext* context)
{
    variable_->setValue(value, context);
}

VariableAccess::~VariableAccess() = default;