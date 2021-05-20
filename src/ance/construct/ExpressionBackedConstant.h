#ifndef ANCE_SRC_ANCE_CONSTRUCT_EXPRESSIONBACKEDCONSTANT_H_
#define ANCE_SRC_ANCE_CONSTRUCT_EXPRESSIONBACKEDCONSTANT_H_

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>

#include "BuildableConstantExpression.h"
#include "Constant.h"

class ConstantExpression;

namespace ance
{
class ExpressionBackedConstant : public Constant
{
	public:
		explicit ExpressionBackedConstant(BuildableConstantExpression* expression);

		ance::Type* getType() override;

		void build(llvm::LLVMContext& c) override;

		llvm::Constant * getNativeConstant() override;

	private:
		BuildableConstantExpression* expression_;
		llvm::Constant* constant_{nullptr};
};
}
#endif
