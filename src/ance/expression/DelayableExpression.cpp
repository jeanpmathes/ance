#include "DelayableExpression.h"

DelayableExpression::DelayableExpression(ance::Location location) : BuildableExpression(location) {}

ance::Value* DelayableExpression::getValue() const
{
    return value_;
}

void DelayableExpression::setValue(ance::Value* value)
{
    value_->setValue(value);
}
