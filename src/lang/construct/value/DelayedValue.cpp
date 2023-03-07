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
    assert(lang::Type::areSame(value->type(), type()) && "Type has to match.");

    value_ = value;
}

void lang::DelayedValue::buildNativeValue(CompileContext& context)
{
    expression_->build(context);
    assert(value_.hasValue() && "setValue must be called in expression when their value is used");
    value_.value()->buildNativeValue(context);
}

llvm::Value* lang::DelayedValue::getNativeValue() const
{
    return value_.value()->getNativeValue();
}
