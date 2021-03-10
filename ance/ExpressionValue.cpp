#include "ExpressionValue.h"

#include "Expression.h"

ance::ExpressionValue::ExpressionValue(Expression* expression) : expression_(expression)
{
}

ance::Type* ance::ExpressionValue::get_type()
{
	return expression_->get_type();
}

llvm::Value* ance::ExpressionValue::get_value(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	return expression_->build(c, m, state, ir, di);
}