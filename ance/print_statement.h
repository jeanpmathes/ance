#pragma once
#include "Statement.h"
class print_statement :
	public Statement
{
public:
	print_statement(unsigned int l, unsigned int c);
	void build(llvm::LLVMContext& c, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di, llvm::Function* func);
	~print_statement();
};
