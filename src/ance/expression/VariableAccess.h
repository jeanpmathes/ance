#ifndef ANCE_SRC_ANCE_EXPRESSION_VARIABLEACCESS_H_
#define ANCE_SRC_ANCE_EXPRESSION_VARIABLEACCESS_H_

#include "BuildableExpression.h"

namespace ance
{
class Variable;

class Scope;
}

class VariableAccess : public BuildableExpression
{
	public:
		explicit VariableAccess(std::string identifier);

		void setScope(ance::Scope* scope) override;

		ance::Type* getType() override;

		ance::Value* getValue() override;

		llvm::Value* build(
			llvm::LLVMContext& c,
			llvm::Module* m,
			CompileState* state,
			llvm::IRBuilder<>& ir,
			llvm::DIBuilder* di
		) override;

		~VariableAccess() override;

	private:
		std::string identifier_;
		ance::Value* value_;
		ance::Variable* variable_{nullptr};
};

#endif