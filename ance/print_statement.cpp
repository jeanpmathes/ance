#include "print_statement.h"
#include "anceConstants.h"

print_statement::print_statement(unsigned int l, unsigned int c) : Statement(c, l)
{
}

void print_statement::build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di, llvm::Function* func)
{
	std::string str = "HELLO WORLD\n";

	llvm::Value* handle_ptr = m->getGlobalVariable(ANCE_STD_OUTPUT_HANDLE);
	llvm::LoadInst* handle = ir.CreateLoad(llvm::Type::getInt8PtrTy(c), handle_ptr, "handle");

	llvm::Constant* buf = ir.CreateGlobalStringPtr(str);
	llvm::ConstantInt* writeNum = llvm::ConstantInt::get(llvm::Type::getInt32Ty(c), str.size());
	llvm::AllocaInst* writtenNum = ir.CreateAlloca(llvm::Type::getInt32Ty(c));
	llvm::ConstantPointerNull* null = llvm::ConstantPointerNull::get(llvm::PointerType::getInt8PtrTy(c));

	state->buildnativecall_WriteFile(handle, buf, writeNum, writtenNum, null);
}

print_statement::~print_statement()
{
}