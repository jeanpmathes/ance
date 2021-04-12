#pragma once
#include "Statement.h"

class BuildableExpression;

class expression_statement : public Statement
{
public:
	expression_statement(ance::Function* function, BuildableExpression* expression, unsigned int l, unsigned int c);
	void build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di) override;
	~expression_statement();

private:
    BuildableExpression* expression_;
};
