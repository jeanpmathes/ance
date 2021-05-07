#include "DeleteStatement.h"

#include "Function.h"
#include "LocalScope.h"

DeleteStatement::DeleteStatement(Expression* to_delete, unsigned int l, unsigned int c) : Statement(l, c), to_delete_(to_delete)
{

}

void DeleteStatement::setContainingFunction(ance::Function* function)
{
	Statement::setContainingFunction(function);

	to_delete_->setScope(function->getScope());
}

void DeleteStatement::build(
	llvm::LLVMContext& c,
	llvm::Module* m,
	CompileState* state,
	llvm::IRBuilder<>& ir,
	llvm::DIBuilder* di
)
{
	state->runtime_->deleteDynamic(to_delete_->getValue(), c, m, state, ir, di);
}

DeleteStatement::~DeleteStatement() = default;
