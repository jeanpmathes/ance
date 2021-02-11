#include "print_statement.h"

#include "anceConstants.h"

#include "Expression.h"
#include "Value.h"

print_statement::print_statement(ance::Function* function, const unsigned int l, const unsigned int c, Expression* expression) : Statement(function, c, l), expression_(expression)
{
}

void print_statement::build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	llvm::Value* handle_ptr = m->getGlobalVariable(ANCE_STD_OUTPUT_HANDLE);
	llvm::LoadInst* handle = ir.CreateLoad(llvm::Type::getInt8PtrTy(c), handle_ptr, "handle");

	llvm::Value* char_arr = expression_->get_value()->get_value(c, m, state, ir, di);

	assert(char_arr->getType()->isArrayTy());
	llvm::Value* write_num = llvm::ConstantInt::get(llvm::Type::getInt32Ty(c), char_arr->getType()->getArrayNumElements());

	llvm::AllocaInst* char_arr_ptr = ir.CreateAlloca(char_arr->getType(), 0, write_num);
	ir.CreateStore(char_arr, char_arr_ptr);

	llvm::Constant* zero = llvm::ConstantInt::get(llvm::Type::getInt64Ty(c), 0);
	llvm::Value* char_ptr = ir.CreateGEP(char_arr_ptr, { zero, zero });

	llvm::AllocaInst* written_num_ptr = ir.CreateAlloca(llvm::Type::getInt32Ty(c));
	llvm::ConstantPointerNull* null = llvm::ConstantPointerNull::get(llvm::PointerType::getInt8PtrTy(c));

	state->buildnativecall_WriteFile(handle, char_ptr, write_num, written_num_ptr, null);
}

print_statement::~print_statement() = default;