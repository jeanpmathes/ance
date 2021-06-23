#pragma once

#include "Statement.h"

namespace ance
{
class LocalVariable;
}

class Expression;

class LocalVariableDefinition : public Statement
{
	public:
		LocalVariableDefinition(
			std::string identifier,
			ance::Type* type,
			Expression* assigned,
			unsigned int l,
			unsigned int c
		);

		void setContainingFunction(ance::DefinedFunction* function) override;

		void build(
			llvm::LLVMContext& c,
			llvm::Module* m,
			CompileState* state,
			llvm::IRBuilder<>& ir,
			llvm::DIBuilder* di
		) override;

	private:
		std::string identifier_;
		ance::Type* type_;
		Expression* assigned_;

		ance::LocalVariable* variable_{nullptr};
};
