#include "DelayableExpression.h"

std::shared_ptr<lang::Value> DelayableExpression::getValue() const
{
    return value_;
}

void DelayableExpression::setValue(std::shared_ptr<lang::Value> const& value)
{
    value_->setValue(value);
}
