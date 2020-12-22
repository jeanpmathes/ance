#include "print_statement.h"
#include "anceConstants.h"

print_statement::print_statement(const unsigned int l, const unsigned int c, Expression* expression) : Statement(c, l), expression_(expression)
{
}

void print_statement::build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	llvm::Value* handle_ptr = m->getGlobalVariable(ANCE_STD_OUTPUT_HANDLE);
	llvm::LoadInst* handle = ir.CreateLoad(llvm::Type::getInt8PtrTy(c), handle_ptr, "handle");

	auto* str_arr_const = static_cast<llvm::Constant*>(expression_->get_value()->get_value(c, m, state, ir, di));
	const int str_length = (static_cast<llvm::ConstantDataArray*>(str_arr_const))->getNumElements();

	llvm::AllocaInst* str_arr_ptr = ir.CreateAlloca(str_arr_const->getType(), 0, llvm::ConstantInt::get(llvm::Type::getInt64Ty(c), str_length));
	ir.CreateStore(str_arr_const, str_arr_ptr);

	llvm::Constant* zero = llvm::ConstantInt::get(llvm::Type::getInt64Ty(c), 0);
	llvm::Value* str_ptr = ir.CreateGEP(str_arr_ptr, { zero, zero });

	llvm::ConstantInt* writeNum = llvm::ConstantInt::get(llvm::Type::getInt32Ty(c), str_length);
	llvm::AllocaInst* writtenNum = ir.CreateAlloca(llvm::Type::getInt32Ty(c));
	llvm::ConstantPointerNull* null = llvm::ConstantPointerNull::get(llvm::PointerType::getInt8PtrTy(c));

	state->buildnativecall_WriteFile(handle, str_ptr, writeNum, writtenNum, null);
}

print_statement::~print_statement() = default;