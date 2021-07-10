#include "ExpressionStatement.h"

#include "BuildableExpression.h"
#include "DefinedFunction.h"
#include "LocalScope.h"

ExpressionStatement::ExpressionStatement(
	BuildableExpression* expression,
	unsigned l,
	unsigned c
)
	: Statement(l, c), expression_(expression)
{
}

void ExpressionStatement::setContainingFunction(ance::DefinedFunction* function)
{
	Statement::setContainingFunction(function);

	expression_->setScope(function->getScope());
}

void ExpressionStatement::build(
	llvm::LLVMContext& c,
	llvm::Module* m,
	CompileContext* state,
	llvm::IRBuilder<>& ir,
	llvm::DIBuilder* di
)
{
	expression_->build(c, m, state, ir, di);
}
