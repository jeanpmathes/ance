#include "ConstantExpression.h"

#include "lang/construct/constant/Constant.h"

std::shared_ptr<lang::Value> ConstantExpression::getValue() const
{
    return getConstantValue();
}
