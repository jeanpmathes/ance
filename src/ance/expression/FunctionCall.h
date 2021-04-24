#ifndef ANCE_SRC_ANCE_EXPRESSION_FUNCTIONCALL_H_
#define ANCE_SRC_ANCE_EXPRESSION_FUNCTIONCALL_H_

#include "BuildableExpression.h"

namespace ance
{
class Scope;
}

class FunctionCall : public BuildableExpression
{
	public:
		FunctionCall(std::string identifier, ance::Scope* scope, std::vector<Expression*> arguments);

		ance::Type* getType() override;

		ance::Value* getValue() override;

		llvm::Value* build(
			llvm::LLVMContext& c,
			llvm::Module* m,
			CompileState* state,
			llvm::IRBuilder<>& ir,
			llvm::DIBuilder* di
		) override;

		~FunctionCall() override;

	private:
		ance::Scope* scope_;
		std::string identifier_;
		std::vector<Expression*> arguments_;
		ance::Value* return_value_;
};

#endif