#include "Value.h"

ance::Value::Value(Expression* expression) : expression_(expression)
{
}

llvm::Value* ance::Value::get_value(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	return expression_->build(c, m, state, ir, di);
}