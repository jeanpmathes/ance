#include "print_statement.h"
#include "anceConstants.h"

#include "Expression.h"
#include "Value.h"

print_statement::print_statement(const unsigned int l, const unsigned int c, Expression* expression) : Statement(c, l), expression_(expression)
{
}

void print_statement::build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	llvm::Value* handle_ptr = m->getGlobalVariable(ANCE_STD_OUTPUT_HANDLE);
	llvm::LoadInst* handle = ir.CreateLoad(llvm::Type::getInt8PtrTy(c), handle_ptr, "handle");

	llvm::Value* char_arr_ptr = expression_->get_value()->get_value(c, m, state, ir, di);

	llvm::Constant* zero = llvm::ConstantInt::get(llvm::Type::getInt64Ty(c), 0);
	llvm::Value* char_ptr = ir.CreateGEP(char_arr_ptr, { zero, zero });

	llvm::ConstantInt* writeNum = llvm::ConstantInt::get(llvm::Type::getInt32Ty(c), 1);
	llvm::AllocaInst* writtenNum = ir.CreateAlloca(llvm::Type::getInt32Ty(c));
	llvm::ConstantPointerNull* null = llvm::ConstantPointerNull::get(llvm::PointerType::getInt8PtrTy(c));

	state->buildnativecall_WriteFile(handle, char_ptr, writeNum, writtenNum, null);
}

print_statement::~print_statement() = default;