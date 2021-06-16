#ifndef ANCE_SRC_ANCE_EXPRESSION_SIZEOFEXPRESSION_H_
#define ANCE_SRC_ANCE_EXPRESSION_SIZEOFEXPRESSION_H_

#include "BuildableExpression.h"

#include "ExpressionBackedValue.h"

class Application;

class SizeofExpression : public BuildableExpression
{
	public:
		explicit SizeofExpression(Expression* expression);

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

	private:
		ance::Value* return_value_{new ance::ExpressionBackedValue(this)};
		Expression* expression_;
};

#endif