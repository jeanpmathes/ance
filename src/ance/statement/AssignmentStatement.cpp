#include "AssignmentStatement.h"

#include "Assignable.h"
#include "Expression.h"
#include "Function.h"
#include "LocalScope.h"

AssignmentStatement::AssignmentStatement(
	Assignable* assignable,
	Expression* assigned,
	unsigned int l,
	unsigned int c
)
	:
	Statement(l, c), assignable_(assignable), assigned_(assigned)
{
}

void AssignmentStatement::setContainingFunction(ance::Function* function)
{
	Statement::setContainingFunction(function);

	assignable_->setScope(function->getScope());
	assigned_->setScope(function->getScope());
}

void AssignmentStatement::build(
	llvm::LLVMContext& c,
	llvm::Module* m,
	CompileState* state,
	llvm::IRBuilder<>& ir,
	llvm::DIBuilder* di
)
{
	assignable_->assign(assigned_->getValue(), c, m, state, ir, di);
}
