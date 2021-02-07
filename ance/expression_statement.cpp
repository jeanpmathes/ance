#include "expression_statement.h"

#include "Expression.h"

expression_statement::expression_statement(Expression* expression, unsigned l, unsigned c) : Statement(l, c), expression_(expression)
{
}

void expression_statement::build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	expression_->build(c, m, state, ir, di);
}

expression_statement::~expression_statement() = default;