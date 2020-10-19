#pragma once
#include "Statement.h"
class return_statement :
	public Statement
{
public:
	return_statement(unsigned int l, unsigned int c, uint32_t code);
	void build(llvm::LLVMContext& c, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di, llvm::Function* func);
	~return_statement();

private:
	uint32_t exit_code;
};
