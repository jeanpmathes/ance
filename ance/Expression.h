#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "Value.h"

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/DIBuilder.h"

#include "CompileState.h"

class CompileState;

namespace ance
{
	class Value;
}

class Expression
{
public:
	virtual ance::Value* get_value() = 0;
	virtual llvm::Value* build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di) = 0;

	virtual ~Expression() = 0;
};
#endif