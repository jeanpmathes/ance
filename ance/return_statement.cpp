#include "return_statement.h"

return_statement::return_statement(unsigned int l, unsigned int c) : Statement(l, c)
{
}

void return_statement::build(llvm::LLVMContext& c, llvm::IRBuilder<>& ir, llvm::DIBuilder* di, llvm::Function* func)
{
	llvm::Value* return_val = llvm::ConstantInt::get(llvm::Type::getInt32Ty(c), 0);
	ir.CreateRet(return_val);
}

return_statement::~return_statement()
{
}