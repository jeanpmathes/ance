#include "VariableAccess.h"

#include <utility>

#include "Value.h"
#include "Scope.h"

VariableAccess::VariableAccess(std::string identifier)
	: identifier_(std::move(identifier))
{
}

void VariableAccess::setScope(ance::Scope* scope)
{
	variable_ = scope->getVariable(identifier_);
}

ance::Type* VariableAccess::getType()
{
	return variable_->type();
}

void VariableAccess::buildValue(CompileContext* context)
{
	ance::Value* value = variable_->getValue(context);
	setValue(value);
}

VariableAccess::~VariableAccess() = default;