#pragma once

#include "Statement.h"

class ReturnStatement :
	public Statement
{
public:
	ReturnStatement(ance::Function* function, unsigned int l, unsigned int c, ance::Value* return_value);
	void build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di) override;
	~ReturnStatement() override;

private:
	ance::Value* return_value_;
};
