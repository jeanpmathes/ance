#include "return_statement.h"
#include "Value.h"

return_statement::return_statement(const unsigned int l, const unsigned int c, ance::Value* return_value) : Statement(l, c), return_value_(return_value)
{
}

void return_statement::build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	assert(return_value_->get_type()->get_name() == "ui32");

	llvm::Value* return_val = return_value_->get_value(c, m, state, ir, di);
	ir.CreateRet(return_val);
}

return_statement::~return_statement() = default;