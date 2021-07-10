#pragma once

#include "Statement.h"
#include "Expression.h"

class ReturnStatement :
	public Statement
{
	public:
		ReturnStatement(Expression* return_value, unsigned int l, unsigned int c);

		void setContainingFunction(ance::DefinedFunction* function) override;

		void build(
			llvm::LLVMContext& c,
			llvm::Module* m,
			CompileContext* state,
			llvm::IRBuilder<>& ir,
			llvm::DIBuilder* di
		) override;

	private:
		Expression* return_value_;
};
