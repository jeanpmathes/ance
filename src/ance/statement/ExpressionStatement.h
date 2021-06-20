#pragma once

#include "Statement.h"

class BackingExpression;

class ExpressionStatement : public Statement
{
	public:
		ExpressionStatement(BackingExpression* expression, unsigned int l, unsigned int c);

		void setContainingFunction(ance::Function* function) override;

		void build(
			llvm::LLVMContext& c,
			llvm::Module* m,
			CompileState* state,
			llvm::IRBuilder<>& ir,
			llvm::DIBuilder* di
		) override;

	private:
		BackingExpression* expression_;
};
