#pragma once
#include "Statement.h"
class return_statement :
	public Statement
{
public:
	return_statement(unsigned int l, unsigned int c);
	void build(llvm::LLVMContext& c, llvm::IRBuilder<>& ir, llvm::DIBuilder* di, llvm::Function* func);
	~return_statement();
};
