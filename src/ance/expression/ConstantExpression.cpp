#include "ConstantExpression.h"

#include "ance/construct/constant/Constant.h"

std::shared_ptr<ance::Value> ConstantExpression::getValue() const
{
    return getConstantValue();
}
