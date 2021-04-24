#include "ReturnStatement.h"
#include "Value.h"
#include "Function.h"

ReturnStatement::ReturnStatement(
	ance::Function* function,
	const unsigned int l,
	const unsigned int c,
	ance::Value* return_value
)
	: Statement(function, l, c), return_value_(return_value)
{
}

void ReturnStatement::build(llvm::LLVMContext&, llvm::Module*, CompileState*, llvm::IRBuilder<>&, llvm::DIBuilder*)
{
	getContainingFunction()->addReturn(return_value_);
}

ReturnStatement::~ReturnStatement() = default;