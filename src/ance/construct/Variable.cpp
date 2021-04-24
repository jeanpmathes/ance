#include "Variable.h"

#include <utility>

ance::Variable::Variable(ance::Scope* containing_scope, std::string identifier, ance::Type* type, bool is_constant)
	:
	identifier_(std::move(identifier)),
	is_defined_(true),
	scope_(containing_scope),
	type_(type),
	is_constant_(is_constant)
{
}

ance::Variable::Variable(std::string identifier)
	:
	identifier_(std::move(identifier)), is_defined_(false), scope_(nullptr), type_(nullptr), is_constant_(true)
{
}

void ance::Variable::define(ance::Scope* containing_scope, ance::Type* type, bool is_constant)
{
	assert(!is_defined_);

	scope_ = containing_scope;
	type_ = type;
	is_constant_ = is_constant;

	is_defined_ = true;
}

bool ance::Variable::isDefined()
{
	return is_defined_;
}

std::string ance::Variable::identifier() const
{
	assert(is_defined_);
	return identifier_;
}

ance::Type* ance::Variable::type() const
{
	assert(is_defined_);
	return type_;
}

bool ance::Variable::isConstant() const
{
	assert(is_defined_);
	return is_constant_;
}