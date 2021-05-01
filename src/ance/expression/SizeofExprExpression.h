#ifndef ANCE_SRC_ANCE_EXPRESSION_SIZEOFEXPREXPRESSION_H_
#define ANCE_SRC_ANCE_EXPRESSION_SIZEOFEXPREXPRESSION_H_

#include "BuildableExpression.h"

class Application;

class SizeofExprExpression : public BuildableExpression
{
	public:
		explicit SizeofExprExpression(Expression* expression);

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

	private:
		ance::Value* return_value_;
		Expression* expression_;
};

#endif