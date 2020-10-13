#pragma once
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/DIBuilder.h"
class Statement
{
public:
	Statement(unsigned int l, unsigned int c);
	unsigned int getLine();
	unsigned int getColumn();
	virtual void build(llvm::LLVMContext& c, llvm::IRBuilder<>& ir, llvm::DIBuilder* di, llvm::Function* func) = 0;
	virtual ~Statement() = 0;

private:
	unsigned int line;
	unsigned int column;
};
