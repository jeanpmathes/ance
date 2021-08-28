#include "ConstantExpression.h"

#include "ance/construct/constant/Constant.h"

ance::Value* ConstantExpression::getValue() const
{
    return getConstantValue();
}
