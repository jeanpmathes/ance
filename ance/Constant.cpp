#include "Constant.h"

ance::Constant::Constant(ConstantExpression* expression) : Value(expression), expression_(expression)
{
}

llvm::Constant* ance::Constant::get_constant(llvm::LLVMContext& c)
{
	return expression_->build_constant(c);
}

llvm::Value* ance::Constant::get_value(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	return get_constant(c);
}