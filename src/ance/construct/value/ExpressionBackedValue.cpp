#include "ExpressionBackedValue.h"

ance::ExpressionBackedValue::ExpressionBackedValue(BackingExpression* expression)
    : expression_(expression)
{
}

ance::Type* ance::ExpressionBackedValue::getType()
{
    return expression_->getType();
}

void ance::ExpressionBackedValue::buildNativeValue(CompileContext* context)
{
    expression_->buildBackingValue(context);
}

llvm::Value* ance::ExpressionBackedValue::getNativeValue()
{
    return expression_->getNativeValue();
}
