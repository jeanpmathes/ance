#include "DelayableExpression.h"

#include "lang/ApplicationVisitor.h"

Shared<lang::Value> DelayableExpression::getValue()
{
    return value_;
}

lang::Value const& DelayableExpression::getValue() const
{
    return *value_;
}

void DelayableExpression::setValue(Shared<lang::Value> value)
{
    delayed_value_->setValue(value);
}
