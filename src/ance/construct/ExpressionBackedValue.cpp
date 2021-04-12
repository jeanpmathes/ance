#include "ExpressionBackedValue.h"

#include "Expression.h"

ance::ExpressionBackedValue::ExpressionBackedValue(BuildableExpression* expression) : expression_(expression)
{
}

ance::Type* ance::ExpressionBackedValue::get_type()
{
	return expression_->get_type();
}

llvm::Value* ance::ExpressionBackedValue::get_value(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	return expression_->build(c, m, state, ir, di);
}