#ifndef ANCE_SRC_ANCE_CONSTRUCT_CONSTANT_EXPRESSIONBACKEDCONSTANT_H_
#define ANCE_SRC_ANCE_CONSTRUCT_CONSTANT_EXPRESSIONBACKEDCONSTANT_H_

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

		llvm::Constant* buildContent(llvm::Module* m) override;

	private:
		BuildableConstantExpression* expression_;
};
}
#endif
