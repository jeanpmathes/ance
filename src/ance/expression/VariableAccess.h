#ifndef ANCE_SRC_ANCE_EXPRESSION_VARIABLEACCESS_H_
#define ANCE_SRC_ANCE_EXPRESSION_VARIABLEACCESS_H_

#include "DelayableExpression.h"
#include "DelayedValue.h"

namespace ance
{
class Variable;

class Scope;
}

class VariableAccess : public DelayableExpression
{
	public:
		explicit VariableAccess(std::string identifier);

		void setScope(ance::Scope* scope) override;

		ance::Type* getType() override;

		ance::Value* getValue() override;

		void build(
			llvm::LLVMContext& c,
			llvm::Module* m,
			CompileState* state,
			llvm::IRBuilder<>& ir,
			llvm::DIBuilder* di
		) override;

		~VariableAccess() override;

	private:
		std::string identifier_;
		ance::DelayedValue* value_{new ance::DelayedValue(this)};
		ance::Variable* variable_{nullptr};
};

#endif