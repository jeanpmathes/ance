#include "ConstantLiteral.h"

#include "Constant.h"
#include "Scope.h"

ConstantLiteral::ConstantLiteral(ance::Constant* constant)
    : constant_(constant)
{
}

ance::Type* ConstantLiteral::getType()
{
    return constant_->getType();
}

ance::Constant* ConstantLiteral::getConstantValue()
{
    return constant_;
}
