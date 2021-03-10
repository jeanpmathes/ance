#include "LocalScope.h"
#include "Constant.h"
#include "GlobalScope.h"
#include "ValueWrapper.h"

ance::LocalScope::LocalScope(ance::Scope* parent) : parent_(parent)
{
}

ance::GlobalScope* ance::LocalScope::get_global_scope()
{
	return parent_->get_global_scope();
}

bool ance::LocalScope::validate()
{
	return true;
}

ance::LocalVariable* ance::LocalScope::define_local_variable(const std::string& identifier, ance::Type* type, Expression* expression)
{
	assert(local_variables.find(identifier) == local_variables.end());

	ance::LocalVariable* variable = new LocalVariable(this, identifier, type, expression->get_value());
	local_variables[identifier] = variable;

	return variable;
}

ance::LocalVariable* ance::LocalScope::define_local_variable(const std::string& identifier, ance::Type* type, ance::Value* value)
{
	assert(local_variables.find(identifier) == local_variables.end());
	ance::LocalVariable* variable = new LocalVariable(this, identifier, type, value);
	local_variables[identifier] = variable;

	return variable;
}

ance::Variable* ance::LocalScope::get_variable(const std::string identifier)
{
	if (local_variables.find(identifier) != local_variables.end())
	{
		return local_variables[identifier];
	}

	return get_global_scope()->get_variable(identifier);
}