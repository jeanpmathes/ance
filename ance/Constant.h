#ifndef ANCE_CONSTANT_H
#define ANCE_CONSTANT_H

#include "ConstantExpression.h"
#include "ExpressionValue.h"

#include "llvm/IR/DIBuilder.h"
#include "llvm/IR/IRBuilder.h"

class ConstantExpression;

namespace ance
{
	class Constant : public ExpressionValue
	{
	public:
		Constant(ConstantExpression* expression);
		llvm::Constant* get_constant(llvm::LLVMContext& c);
		llvm::Value* get_value(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di) override;

	private:
		ConstantExpression* expression_;
	};
}
#endif