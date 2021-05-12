#include "RoughCast.h"

#include "RoughlyCastedValue.h"

RoughCast::RoughCast(ance::Type* target_type, Expression* expression)
	: target_type_(target_type),
	  expression_(expression),
	  return_value_(new ance::RoughlyCastedValue(target_type, expression->getValue()))
{

}

void RoughCast::setScope(ance::Scope* scope)
{
	expression_->setScope(scope);
}

ance::Type* RoughCast::getType()
{
	return target_type_;
}

ance::Value* RoughCast::getValue()
{
	return return_value_;
}

RoughCast::~RoughCast() = default;
