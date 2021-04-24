#include "ExpressionStatement.h"

#include "BuildableExpression.h"

ExpressionStatement::ExpressionStatement(
	ance::Function* function,
	BuildableExpression* expression,
	unsigned l,
	unsigned c
)
	: Statement(function, l, c), expression_(expression)
{
}

void ExpressionStatement::build(
	llvm::LLVMContext& c,
	llvm::Module* m,
	CompileState* state,
	llvm::IRBuilder<>& ir,
	llvm::DIBuilder* di
)
{
	expression_->build(c, m, state, ir, di);
}

ExpressionStatement::~ExpressionStatement() = default;