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

		void buildNativeValue(CompileContext* context) override;

		llvm::Value* getNativeValue() override;

	private:
		BackingExpression* expression_;
};
}
#endif