#include "ExpressionBackedValue.h"

#include "lang/expression/BackingExpression.h"

lang::ExpressionBackedValue::ExpressionBackedValue(BackingExpression* expression) : expression_(expression) {}

lang::ResolvingHandle<lang::Type> lang::ExpressionBackedValue::type()
{
    return expression_->type();
}

void lang::ExpressionBackedValue::buildNativeValue(CompileContext* context)
{
    expression_->build(context);
}

llvm::Value* lang::ExpressionBackedValue::getNativeValue()
{
    return expression_->getNativeValue();
}
