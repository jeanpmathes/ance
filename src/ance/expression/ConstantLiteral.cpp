#include "ConstantLiteral.h"

#include "ance/construct/constant/Constant.h"
#include "ance/scope/Scope.h"

ConstantLiteral::ConstantLiteral(ance::Constant* constant, ance::Location location)
    : Expression(location)
    , constant_(constant)
{}

ance::Type* ConstantLiteral::type()
{
    return constant_->type();
}

void ConstantLiteral::validate(ValidationLogger&) {}

ance::Constant* ConstantLiteral::getConstantValue() const
{
    return constant_;
}
