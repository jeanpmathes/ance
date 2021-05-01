#include "ReturnStatement.h"

#include "Value.h"
#include "Function.h"
#include "LocalScope.h"

ReturnStatement::ReturnStatement(
	Expression* return_value,
	const unsigned int l,
	const unsigned int c
)
	: Statement(l, c), return_value_(return_value)
{
}

void ReturnStatement::setContainingFunction(ance::Function* function)
{
	Statement::setContainingFunction(function);

	return_value_->setScope(function->getScope());
}

void ReturnStatement::build(llvm::LLVMContext&, llvm::Module*, CompileState*, llvm::IRBuilder<>&, llvm::DIBuilder*)
{
	getContainingFunction()->addReturn(return_value_ ? return_value_->getValue() : nullptr);
}

ReturnStatement::~ReturnStatement() = default;