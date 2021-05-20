#ifndef ANCE_SRC_ANCE_CONSTRUCT_CONSTANT_H_
#define ANCE_SRC_ANCE_CONSTRUCT_CONSTANT_H_

#include "ConstantExpression.h"
#include "ExpressionBackedValue.h"

#include "llvm/IR/DIBuilder.h"
#include "llvm/IR/IRBuilder.h"

namespace ance
{
class Constant : public Value
{
	public:
		virtual void build(llvm::LLVMContext& c) = 0;

		virtual llvm::Constant* getNativeConstant() = 0;

		llvm::Value* getValue(
			llvm::LLVMContext& c,
			llvm::Module* m,
			CompileState* state,
			llvm::IRBuilder<>& ir,
			llvm::DIBuilder* di
		) override;

};
}
#endif