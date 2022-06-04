#include "DelayedValue.h"

#include "lang/expression/DelayableExpression.h"

lang::DelayedValue::DelayedValue(DelayableExpression& expression) : expression_(expression) {}

lang::ResolvingHandle<lang::Type> lang::DelayedValue::type()
{
    return expression_.type();
}

void lang::DelayedValue::setValue(const std::shared_ptr<lang::Value>& value)
{
    assert(!value_);
    assert(lang::Type::areSame(value->type(), type()) && "Type has to match.");

    value_ = value;
}

void lang::DelayedValue::buildNativeValue(CompileContext* context)
{
    expression_.build(context);
    value_->buildNativeValue(context);
}

llvm::Value* lang::DelayedValue::getNativeValue()
{
    return value_->getNativeValue();
}
