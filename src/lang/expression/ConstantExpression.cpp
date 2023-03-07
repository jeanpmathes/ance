#include "ConstantExpression.h"

#include "lang/ApplicationVisitor.h"
#include "lang/construct/constant/Constant.h"

Shared<lang::Value> ConstantExpression::getValue()
{
    return getConstantValue();
}

lang::Value const& ConstantExpression::getValue() const
{
    return getConstantValue();
}
