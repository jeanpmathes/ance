#include "PrintStatement.h"

#include "anceConstants.h"

#include "Expression.h"
#include "Value.h"
#include "Function.h"
#include "LocalScope.h"
#include "PointerType.h"
#include "IntegerType.h"

PrintStatement::PrintStatement(
	Expression* str, Expression* len,
	const unsigned int l,
	const unsigned int c
)
	: Statement(l, c), str_(str), len_(len)
{
}

void PrintStatement::setContainingFunction(ance::Function* function)
{
	Statement::setContainingFunction(function);

	str_->setScope(function->getScope());
	len_->setScope(function->getScope());
}

void PrintStatement::build(
	llvm::LLVMContext& c,
	llvm::Module* m,
	CompileState* state,
	llvm::IRBuilder<>& ir,
	llvm::DIBuilder* di
)
{
	assert(ance::PointerType::isPointerType(str_->getType()) && "First argument must be pointer.");

	llvm::Value* handle_ptr = m->getGlobalVariable(ANCE_STD_OUTPUT_HANDLE);
	llvm::LoadInst* handle = ir.CreateLoad(llvm::Type::getInt8PtrTy(c), handle_ptr, "handle");

	ance::Value* str_ptr = str_->getValue();
	ance::Value* str_len = len_->getValue();

	str_ptr->build(c, m, state, ir, di);
	str_len->build(c, m, state, ir, di);

	llvm::Value* native_char_ptr = str_ptr->getContentValue(c, m, state, ir, di);
	llvm::Value* native_str_len = str_len->getContentValue(c, m, state, ir, di);

	llvm::AllocaInst* written_num_ptr = ir.CreateAlloca(llvm::Type::getInt32Ty(c));
	llvm::ConstantPointerNull* null = llvm::ConstantPointerNull::get(llvm::PointerType::getInt8PtrTy(c));

	state->buildnativecall_WriteFile(handle, native_char_ptr, native_str_len, written_num_ptr, null);
}
