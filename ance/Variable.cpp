#include "Variable.h"

ance::Variable::Variable(ance::Scope* containing_scope, std::string identifier, ance::Type* type, bool is_constant) :
	scope_(containing_scope), identifier_(identifier), type_(type), is_constant_(is_constant)
{
}

std::string ance::Variable::identifier() const
{
	return identifier_;
}

ance::Type* ance::Variable::type() const
{
	return type_;
}

bool ance::Variable::is_constant() const
{
	return is_constant_;
}