#include "VariableAccess.h"

#include <utility>

#include "ance/construct/value/Value.h"
#include "ance/scope/Scope.h"

VariableAccess::VariableAccess(std::string identifier, ance::Location location)
    : Expression(location)
    , identifier_(std::move(identifier))
{}

void VariableAccess::setScope(ance::Scope* scope)
{
    variable_ = scope->getVariable(identifier_);
}

ance::Type* VariableAccess::type()
{
    return variable_->type();
}

void VariableAccess::validate(ValidationLogger&)
{
    assert(variable_->isDefined() && "Variable must be defined to access it.");
}

void VariableAccess::doBuild(CompileContext* context)
{
    ance::Value* value = variable_->getValue(context);
    setValue(value);
}

VariableAccess::~VariableAccess() = default;