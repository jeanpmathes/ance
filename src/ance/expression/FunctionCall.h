#ifndef ANCE_SRC_ANCE_EXPRESSION_FUNCTIONCALL_H_
#define ANCE_SRC_ANCE_EXPRESSION_FUNCTIONCALL_H_

#include "BuildableExpression.h"

#include "ExpressionBackedValue.h"

namespace ance
{
class Scope;
}

class FunctionCall : public BuildableExpression
{
	public:
		FunctionCall(std::string identifier, std::vector<Expression*> arguments);

		void setScope(ance::Scope* scope) override;

		ance::Type* getType() override;

		ance::Value* getValue() override;

		llvm::Value* buildNativeValue(
			llvm::LLVMContext& c,
			llvm::Module* m,
			CompileState* state,
			llvm::IRBuilder<>& ir,
			llvm::DIBuilder* di
		) override;

		~FunctionCall() override;

	private:
		std::string identifier_;
		std::vector<Expression*> arguments_;
		ance::Value* return_value_{new ance::ExpressionBackedValue(this)};
		ance::Scope* scope_{nullptr};
};

#endif