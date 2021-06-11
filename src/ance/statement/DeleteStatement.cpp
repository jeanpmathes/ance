#include "DeleteStatement.h"

#include "Function.h"
#include "LocalScope.h"

DeleteStatement::DeleteStatement(Expression* to_delete, bool delete_buffer, unsigned int l, unsigned int c)
	: Statement(l, c), to_delete_(to_delete), delete_buffer_(delete_buffer)
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
	state->runtime_->deleteDynamic(to_delete_->getValue(), delete_buffer_, c, m, state, ir, di);
}
