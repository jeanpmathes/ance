#include "RoughCast.h"

#include "ance/construct/value/RoughlyCastedValue.h"

RoughCast::RoughCast(ance::Type* target_type, Expression* expression)
    : target_type_(target_type)
    , expression_(expression)
    , return_value_(new ance::RoughlyCastedValue(target_type, expression->getValue()))
{}

void RoughCast::setContainingScope(ance::Scope* scope)
{
    expression_->setContainingScope(scope);
}

ance::Type* RoughCast::type()
{
    return target_type_;
}

ance::Value* RoughCast::getValue() const
{
    return return_value_;
}

RoughCast::~RoughCast() = default;
