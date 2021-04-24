#ifndef ANCE_SRC_ANCE_CONSTRUCT_EXPRESSIONBACKEDVALUE_H_
#define ANCE_SRC_ANCE_CONSTRUCT_EXPRESSIONBACKEDVALUE_H_

#include "Value.h"
#include "BuildableExpression.h"

namespace ance
{
class ExpressionBackedValue : public Value
{
	public:
		explicit ExpressionBackedValue(BuildableExpression* expression);

		ance::Type* getType() override;

		llvm::Value* getValue(
			llvm::LLVMContext& c,
			llvm::Module* m,
			CompileState* state,
			llvm::IRBuilder<>& ir,
			llvm::DIBuilder* di
		) override;

	private:
		BuildableExpression* expression_;
};
}
#endif