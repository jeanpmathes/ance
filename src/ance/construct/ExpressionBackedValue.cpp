#include "ExpressionBackedValue.h"

#include "Expression.h"

ance::ExpressionBackedValue::ExpressionBackedValue(BuildableExpression* expression)
	: expression_(expression)
{
}

ance::Type* ance::ExpressionBackedValue::getType()
{
	return expression_->getType();
}

llvm::Value* ance::ExpressionBackedValue::getValue(
	llvm::LLVMContext& c,
	llvm::Module* m,
	CompileState* state,
	llvm::IRBuilder<>& ir,
	llvm::DIBuilder* di
)
{
	return expression_->build(c, m, state, ir, di);
}