#include "PrintStatement.h"

#include "anceConstants.h"

#include "Expression.h"
#include "Value.h"
#include "Function.h"
#include "LocalScope.h"

PrintStatement::PrintStatement(
	Expression* expression,
	const unsigned int l,
	const unsigned int c
)
	: Statement(l, c), expression_(expression)
{
}

void PrintStatement::setContainingFunction(ance::Function* function)
{
	Statement::setContainingFunction(function);

	expression_->setScope(function->getScope());
}

void PrintStatement::build(
	llvm::LLVMContext& c,
	llvm::Module* m,
	CompileState* state,
	llvm::IRBuilder<>& ir,
	llvm::DIBuilder* di
)
{
	llvm::Value* handle_ptr = m->getGlobalVariable(ANCE_STD_OUTPUT_HANDLE);
	llvm::LoadInst* handle = ir.CreateLoad(llvm::Type::getInt8PtrTy(c), handle_ptr, "handle");

	ance::Value* char_arr = expression_->getValue();
	char_arr->build(c, m, state, ir, di);
	llvm::Value* native_char_arr = char_arr->getContentValue(c, m, state, ir, di);

	assert(native_char_arr->getType()->isArrayTy());
	llvm::Value
		* write_num =
		llvm::ConstantInt::get(llvm::Type::getInt32Ty(c), native_char_arr->getType()->getArrayNumElements());

	llvm::AllocaInst* char_arr_ptr = ir.CreateAlloca(native_char_arr->getType(), 0, write_num);
	ir.CreateStore(native_char_arr, char_arr_ptr);

	llvm::Constant* zero = llvm::ConstantInt::get(llvm::Type::getInt64Ty(c), 0);
	llvm::Value* char_ptr = ir.CreateGEP(char_arr_ptr, {zero, zero});

	llvm::AllocaInst* written_num_ptr = ir.CreateAlloca(llvm::Type::getInt32Ty(c));
	llvm::ConstantPointerNull* null = llvm::ConstantPointerNull::get(llvm::PointerType::getInt8PtrTy(c));

	state->buildnativecall_WriteFile(handle, char_ptr, write_num, written_num_ptr, null);
}

PrintStatement::~PrintStatement() = default;