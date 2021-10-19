#include "DelayableExpression.h"

std::shared_ptr<ance::Value> DelayableExpression::getValue() const
{
    return value_;
}

void DelayableExpression::setValue(const std::shared_ptr<ance::Value>& value)
{
    value_->setValue(value);
}
