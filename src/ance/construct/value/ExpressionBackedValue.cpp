#include "ExpressionBackedValue.h"

#include "ance/expression/BackingExpression.h"

ance::ExpressionBackedValue::ExpressionBackedValue(BackingExpression* expression) : expression_(expression) {}

ance::Type* ance::ExpressionBackedValue::type()
{
    return expression_->type();
}

void ance::ExpressionBackedValue::buildNativeValue(CompileContext* context)
{
    expression_->build(context);
}

llvm::Value* ance::ExpressionBackedValue::getNativeValue()
{
    return expression_->getNativeValue();
}
