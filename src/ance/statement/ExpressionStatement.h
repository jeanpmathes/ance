#pragma once

#include "Statement.h"

class BuildableExpression;

class ExpressionStatement : public Statement
{
	public:
		ExpressionStatement(BuildableExpression* expression, unsigned int l, unsigned int c);

		void setContainingFunction(ance::DefinedFunction* function) override;

		void build(
			llvm::LLVMContext& c,
			llvm::Module* m,
			CompileContext* state,
			llvm::IRBuilder<>& ir,
			llvm::DIBuilder* di
		) override;

	private:
		BuildableExpression* expression_;
};
