#ifndef STATEMENT_H
#define STATEMENT_H

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/DIBuilder.h"

#include "CompileState.h"

class CompileState;

namespace ance
{
	class Function;
}

class Statement
{
public:
	Statement(ance::Function* function, unsigned int l, unsigned int c);
	ance::Function* get_containing_function() const;
	unsigned int getLine() const;
	unsigned int getColumn() const;
	virtual void build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di) = 0;
	virtual ~Statement() = 0;

private:
	ance::Function* function_;
	unsigned int line;
	unsigned int column;
};

#endif