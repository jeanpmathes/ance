#pragma once

#include "Statement.h"

class Assignable;

class Expression;

class AssignmentStatement : public Statement
{
	public:
		AssignmentStatement(
			Assignable* assignable,
			Expression* assigned,
			unsigned int l,
			unsigned int c
		);

		void setContainingFunction(ance::Function* function) override;

		void build(
			llvm::LLVMContext& c,
			llvm::Module* m,
			CompileState* state,
			llvm::IRBuilder<>& ir,
			llvm::DIBuilder* di
		) override;

		~AssignmentStatement() override;

	private:
		Assignable* assignable_;
		Expression* assigned_;
};
