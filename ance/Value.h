#ifndef ANCE_VALUE_H
#define ANCE_VALUE_H

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/DIBuilder.h"

class Expression;
class CompileState;

namespace ance
{
	class Value
	{
	public:
		Value(Expression* expression);
		llvm::Value* get_value(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di);

	private:
		Expression* expression_;
	};
}
#endif