#include "ExpressionBackedValue.h"

ance::ExpressionBackedValue::ExpressionBackedValue(BuildableExpression* expression)
	: expression_(expression)
{
}

ance::Type* ance::ExpressionBackedValue::getType()
{
	return expression_->getType();
}

void ance::ExpressionBackedValue::build(
	llvm::LLVMContext& c,
	llvm::Module* m,
	CompileState* state,
	llvm::IRBuilder<>& ir,
	llvm::DIBuilder* di
)
{
	expression_->build(c, m, state, ir, di);
}

llvm::Value* ance::ExpressionBackedValue::getNativeValue()
{
	return expression_->getNativeValue();
}
