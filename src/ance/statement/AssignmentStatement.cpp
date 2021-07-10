#include "AssignmentStatement.h"

#include "Assignable.h"
#include "Expression.h"
#include "DefinedFunction.h"
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

void AssignmentStatement::setContainingFunction(ance::DefinedFunction* function)
{
	Statement::setContainingFunction(function);

	assignable_->setScope(function->getScope());
	assigned_->setScope(function->getScope());
}

void AssignmentStatement::build(
	llvm::LLVMContext& c,
	llvm::Module* m,
	CompileContext* state,
	llvm::IRBuilder<>& ir,
	llvm::DIBuilder* di
)
{
	assignable_->assign(assigned_->getValue(), c, m, state, ir, di);
}
