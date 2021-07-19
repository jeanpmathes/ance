#include "ConstantExpression.h"

#include "ance/construct/constant/Constant.h"

ance::Value* ConstantExpression::getValue()
{
    return getConstantValue();
}
