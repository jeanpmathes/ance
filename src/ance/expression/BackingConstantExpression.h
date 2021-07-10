#ifndef ANCE_SRC_ANCE_EXPRESSION_BACKINGCONSTANTEXPRESSION_H_
#define ANCE_SRC_ANCE_EXPRESSION_BACKINGCONSTANTEXPRESSION_H_

#include "ConstantExpression.h"
#include "BackingExpression.h"

class BackingConstantExpression : public ConstantExpression, public BackingExpression
{
	public:
		void buildConstant(llvm::LLVMContext& c);

		ance::Type* getType() override = 0;

		ance::Constant* getConstantValue() override = 0;

		llvm::Constant* getContentConstant();

	protected:
		virtual llvm::Constant* buildContentConstant(llvm::LLVMContext& c) = 0;

		llvm::Value* buildNativeValue(
			llvm::LLVMContext& c,
			llvm::Module* m,
			CompileContext* state,
			llvm::IRBuilder<>& ir,
			llvm::DIBuilder* di
		) final;

	private:
		llvm::Constant* content_constant_{nullptr};
};

#endif
