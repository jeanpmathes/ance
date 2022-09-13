#include "DelayableExpression.h"

std::shared_ptr<lang::Value> DelayableExpression::getValue() const
{
    return value_;
}

void DelayableExpression::setValue(const std::shared_ptr<lang::Value>& value)
{
    value_->setValue(value);
}

