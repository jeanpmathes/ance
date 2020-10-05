#include "return_statement.h"

void return_statement::Build(llvm::LLVMContext& c, llvm::IRBuilder<>& ir)
{
	llvm::Value* return_val = llvm::ConstantInt::get(llvm::Type::getInt32Ty(c), 0);
	ir.CreateRet(return_val);
}

return_statement::~return_statement()
{
}