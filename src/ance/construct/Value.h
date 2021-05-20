#ifndef ANCE_SRC_ANCE_CONSTRUCT_VALUE_H_
#define ANCE_SRC_ANCE_CONSTRUCT_VALUE_H_

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/DIBuilder.h"

class Expression;

class CompileState;

namespace ance
{
class Type;

class Value
{
	public:
		virtual ance::Type* getType() = 0;

		virtual void build(
			llvm::LLVMContext& c,
			llvm::Module* m,
			CompileState* state,
			llvm::IRBuilder<>& ir,
			llvm::DIBuilder* di
		) = 0;

		virtual llvm::Value* getNativeValue() = 0;
};
}
#endif