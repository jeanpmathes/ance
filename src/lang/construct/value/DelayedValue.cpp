#include "DelayedValue.h"

#include <utility>

#include "lang/ApplicationVisitor.h"
#include "lang/expression/DelayableExpression.h"

lang::DelayedValue::DelayedValue(Passed<DelayableExpression> expression) : expression_(std::move(expression)) {}

lang::ResolvingHandle<lang::Type> lang::DelayedValue::type()
{
    return expression_->type();
}

lang::Type const& lang::DelayedValue::type() const
{
    return expression_->type();
}

void lang::DelayedValue::setValue(Shared<lang::Value> value)
{
    assert(not value_.hasValue());
    assert(lang::Type::areSame(value->type(), type()));

    value_ = value;
}

void lang::DelayedValue::buildNativeValue(CompileContext& context)
{
    if (!built_)
    {
        expression_->build(context);
        assert(value_.hasValue());
        built_ = true;
    }

    value_.value()->buildNativeValue(context);
    native_value_ = value_.value()->getNativeValue();
}

void lang::DelayedValue::buildContentValue(CompileContext& context)
{
    if (!built_)
    {
        expression_->build(context);
        assert(value_.hasValue());
        built_ = true;
    }

    value_.value()->buildContentValue(context);
    content_value_ = value_.value()->getContentValue();
}
