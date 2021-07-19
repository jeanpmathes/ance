#include "ConstantLiteral.h"

#include "ance/construct/constant/Constant.h"
#include "ance/scope/Scope.h"

ConstantLiteral::ConstantLiteral(ance::Constant* constant)
    : constant_(constant)
{
}

ance::Type* ConstantLiteral::type()
{
    return constant_->type();
}

ance::Constant* ConstantLiteral::getConstantValue()
{
    return constant_;
}
