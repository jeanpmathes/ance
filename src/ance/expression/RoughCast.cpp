#include "RoughCast.h"

#include "ance/construct/value/RoughlyCastedValue.h"
#include "ance/type/Type.h"

RoughCast::RoughCast(ance::Type* target_type, Expression* expression, ance::Location location)
    : Expression(location)
    , target_type_(target_type)
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

void RoughCast::validate(ValidationLogger& validation_logger)
{
    expression_->validate(validation_logger);
}

ance::Value* RoughCast::getValue() const
{
    return return_value_;
}

RoughCast::~RoughCast() = default;
