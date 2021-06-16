#ifndef ANCE_SRC_ANCE_EXPRESSION_SIZEOFTYPE_H_
#define ANCE_SRC_ANCE_EXPRESSION_SIZEOFTYPE_H_

#include "BuildableExpression.h"

#include "ExpressionBackedValue.h"

class Application;

class SizeofType : public BuildableExpression
{
	public:
		explicit SizeofType(ance::Type* type);

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
		ance::Type* type_;
};

#endif