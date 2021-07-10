#ifndef ANCE_SRC_ANCE_ASSIGNABLE_VARIABLEASSIGNABLE_H_
#define ANCE_SRC_ANCE_ASSIGNABLE_VARIABLEASSIGNABLE_H_

#include "Assignable.h"
#include "Scope.h"
#include "Value.h"

class VariableAssignable : public Assignable
{
	public:
		explicit VariableAssignable(std::string variable_identifier);

		void setScope(ance::Scope* scope) override;

		void assign(
			ance::Value* value,
			llvm::LLVMContext& c,
			llvm::Module* m,
			CompileContext* state,
			llvm::IRBuilder<>& ir,
			llvm::DIBuilder* di
		) override;

	private:
		std::string variable_identifier_;
		ance::Scope* scope_{nullptr};
};

#endif
