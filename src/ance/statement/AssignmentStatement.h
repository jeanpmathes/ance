#pragma once

#include "Statement.h"

class Expression;

class AssignmentStatement : public Statement
{
	public:
		AssignmentStatement(
			std::string variable_identifier,
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
		std::string variable_identifier_;
		Expression* assigned_;
};
