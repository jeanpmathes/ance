#pragma once
#include "Statement.h"
class return_statement :
	public Statement
{
public:
	void Build(llvm::LLVMContext& c, llvm::IRBuilder<>& ir);
	~return_statement();
};
