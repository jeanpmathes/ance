#ifndef ANCE_SRC_ANCE_EXPRESSION_BACKINGEXPRESSION_H_
#define ANCE_SRC_ANCE_EXPRESSION_BACKINGEXPRESSION_H_

#include "Expression.h"
#include "BuildableExpression.h"

class BackingExpression : public virtual Expression, public BuildableExpression
{
	public:
		void buildBackingValue(
			llvm::LLVMContext& c,
			llvm::Module* m,
			CompileState* state,
			llvm::IRBuilder<>& ir,
			llvm::DIBuilder* di
		);

		void build(
			llvm::LLVMContext& c,
			llvm::Module* m,
			CompileState* state,
			llvm::IRBuilder<>& ir,
			llvm::DIBuilder* di
		) final;

		llvm::Value* getNativeValue();

	protected:
		virtual llvm::Value* buildNativeValue(
			llvm::LLVMContext& c,
			llvm::Module* m,
			CompileState* state,
			llvm::IRBuilder<>& ir,
			llvm::DIBuilder* di
		) = 0;

	private:
		llvm::Value* native_value_{nullptr};
};

#endif
