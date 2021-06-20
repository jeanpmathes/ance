#ifndef ANCE_SRC_ANCE_EXPRESSION_DELAYABLEEXPRESSION_H_
#define ANCE_SRC_ANCE_EXPRESSION_DELAYABLEEXPRESSION_H_

#include "Expression.h"

#include "DelayedValue.h"
#include "BuildableExpression.h"

class DelayableExpression : public virtual Expression, public BuildableExpression
{
	public:
		virtual void buildValue(
			llvm::LLVMContext& c,
			llvm::Module* m,
			CompileState* state,
			llvm::IRBuilder<>& ir,
			llvm::DIBuilder* di
		) = 0;

		void build(llvm::LLVMContext &c, llvm::Module *m, CompileState *state, llvm::IRBuilder<> &ir, llvm::DIBuilder *di) final;

		ance::Value* getValue() override;

	protected:
		void setValue(ance::Value* value);

	private:
		ance::DelayedValue* value_{new ance::DelayedValue(this)};
};

#endif
