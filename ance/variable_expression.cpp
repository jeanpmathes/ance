#include "variable_expression.h"

variable_expression::variable_expression() : value_(nullptr)
{
}

ance::Value* variable_expression::get_value()
{
	return value_;
}

llvm::Value* variable_expression::build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
}

variable_expression::~variable_expression() = default;