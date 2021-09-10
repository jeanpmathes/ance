#include "VariableAssignable.h"

VariableAssignable::VariableAssignable(std::string variable_identifier, ance::Location location)
    : Assignable(location)
    , variable_identifier_(std::move(variable_identifier))
{}

void VariableAssignable::setScope(ance::Scope* scope)
{
    scope_ = scope;
}

void VariableAssignable::validate(ValidationLogger& validation_logger)
{
    ance::Variable* variable = scope_->getVariable(variable_identifier_);
    variable->validateSetValue(assigned(), validation_logger, location(), assignedLocation());
}

void VariableAssignable::doBuild(CompileContext* context)
{
    ance::Variable* variable = scope_->getVariable(variable_identifier_);
    variable->setValue(assigned(), context);
}
