#include "DelayableExpression.h"

ance::Value* DelayableExpression::getValue() const
{
    return value_;
}

void DelayableExpression::setValue(ance::Value* value)
{
    value_->setValue(value);
}
