#ifndef ANCE_SRC_ANCE_EXPRESSION_SIZEOFEXPREXPRESSION_H_
#define ANCE_SRC_ANCE_EXPRESSION_SIZEOFEXPREXPRESSION_H_

#include "BuildableExpression.h"

class Application;

class SizeofExprExpression : public BuildableExpression
{
	public:
		SizeofExprExpression(Expression* expression);

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
		ance::Type* return_type_;
		Expression* expression_;
};

#endif