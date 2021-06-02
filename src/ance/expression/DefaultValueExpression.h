#ifndef ANCE_SRC_ANCE_EXPRESSION_DEFAULTVALUEEXPRESSION_H_
#define ANCE_SRC_ANCE_EXPRESSION_DEFAULTVALUEEXPRESSION_H_

#include "BuildableConstantExpression.h"

#include "ExpressionBackedConstant.h"

class DefaultValueExpression : public BuildableConstantExpression
{
	public:
		explicit DefaultValueExpression(ance::Type* type);

		ance::Type* getType() override;

		ance::Value* getValue() override;

		llvm::Value* build(
			llvm::LLVMContext& c,
			llvm::Module* m,
			CompileState* state,
			llvm::IRBuilder<>& ir,
			llvm::DIBuilder* di
		) override;

		ance::Constant* getConstantValue() override;

		llvm::Constant* buildConstant(llvm::LLVMContext& c) override;

		~DefaultValueExpression() override;

	private:
		ance::Type* type_;
		ance::Constant* constant_{new ance::ExpressionBackedConstant(this)};
};

#endif