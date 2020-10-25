#include "return_statement.h"

return_statement::return_statement(unsigned int l, unsigned int c, uint32_t code) : Statement(l, c)
{
	exit_code = code;
}

void return_statement::build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di, llvm::Function* func)
{
	llvm::Value* return_val = llvm::ConstantInt::get(llvm::Type::getInt32Ty(c), exit_code);
	ir.CreateRet(return_val);
}

return_statement::~return_statement()
{
}