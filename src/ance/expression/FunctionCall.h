#ifndef ANCE_SRC_ANCE_EXPRESSION_FUNCTIONCALL_H_
#define ANCE_SRC_ANCE_EXPRESSION_FUNCTIONCALL_H_

#include "DelayableExpression.h"

namespace ance
{
class Scope;
}

class FunctionCall : public DelayableExpression
{
	public:
		FunctionCall(std::string identifier, std::vector<Expression*> arguments);

		void setScope(ance::Scope* scope) override;

		ance::Type* getType() override;

		void buildValue(
			llvm::LLVMContext& c,
			llvm::Module* m,
			CompileContext* state,
			llvm::IRBuilder<>& ir,
			llvm::DIBuilder* di
		) override;

		~FunctionCall() override;

	private:
		std::string identifier_;
		std::vector<Expression*> arguments_;
		ance::Scope* scope_{nullptr};
};

#endif