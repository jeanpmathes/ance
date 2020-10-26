#include "print_statement.h"
#include "anceConstants.h"

print_statement::print_statement(const unsigned int l, const unsigned int c, std::string str) : Statement(c, l), string(str)
{
}

void print_statement::build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di, llvm::Function* func)
{
	llvm::Value* handle_ptr = m->getGlobalVariable(ANCE_STD_OUTPUT_HANDLE);
	llvm::LoadInst* handle = ir.CreateLoad(llvm::Type::getInt8PtrTy(c), handle_ptr, "handle");

	llvm::Constant* buf = ir.CreateGlobalStringPtr(string);
	llvm::ConstantInt* writeNum = llvm::ConstantInt::get(llvm::Type::getInt32Ty(c), string.size());
	llvm::AllocaInst* writtenNum = ir.CreateAlloca(llvm::Type::getInt32Ty(c));
	llvm::ConstantPointerNull* null = llvm::ConstantPointerNull::get(llvm::PointerType::getInt8PtrTy(c));

	state->buildnativecall_WriteFile(handle, buf, writeNum, writtenNum, null);
}

print_statement::~print_statement() = default;