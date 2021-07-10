#ifndef ANCE_SRC_ANCE_CONSTRUCT_VALUE_EXPRESSIONBACKEDVALUE_H_
#define ANCE_SRC_ANCE_CONSTRUCT_VALUE_EXPRESSIONBACKEDVALUE_H_

#include "Value.h"
#include "BackingExpression.h"

namespace ance
{
class ExpressionBackedValue : public Value
{
	public:
		explicit ExpressionBackedValue(BackingExpression* expression);

		ance::Type* getType() override;

		void buildNativeValue(
			llvm::LLVMContext& c,
			llvm::Module* m,
			CompileContext* state,
			llvm::IRBuilder<>& ir,
			llvm::DIBuilder* di
		) override;

		llvm::Value* getNativeValue() override;

	private:
		BackingExpression* expression_;
};
}
#endif