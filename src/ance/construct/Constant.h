#ifndef ANCE_CONSTANT_H
#define ANCE_CONSTANT_H

#include "ConstantExpression.h"
#include "ExpressionBackedValue.h"

#include "llvm/IR/DIBuilder.h"
#include "llvm/IR/IRBuilder.h"

namespace ance
{
	class Constant : public Value
	{
	public:
		virtual llvm::Constant* get_constant(llvm::LLVMContext& c) = 0;
		llvm::Value* get_value(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di) override;

	};
}
#endif