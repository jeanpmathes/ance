#include "ExpressionBackedValue.h"

ance::ExpressionBackedValue::ExpressionBackedValue(BackingExpression* expression)
	: expression_(expression)
{
}

ance::Type* ance::ExpressionBackedValue::getType()
{
	return expression_->getType();
}

void ance::ExpressionBackedValue::buildNativeValue(
	llvm::LLVMContext& c,
	llvm::Module* m,
	CompileState* state,
	llvm::IRBuilder<>& ir,
	llvm::DIBuilder* di
)
{
	expression_->buildBackingValue(c, m, state, ir, di);
}

llvm::Value* ance::ExpressionBackedValue::getNativeValue()
{
	return expression_->getNativeValue();
}
