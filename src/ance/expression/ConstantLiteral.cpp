#include "ConstantLiteral.h"

#include "ance/construct/constant/Constant.h"
#include "ance/scope/Scope.h"

ConstantLiteral::ConstantLiteral(ance::Constant* constant) : constant_(constant) {}

ance::Type* ConstantLiteral::type()
{
    return constant_->type();
}

void ConstantLiteral::validate() {}

ance::Constant* ConstantLiteral::getConstantValue() const
{
    return constant_;
}
