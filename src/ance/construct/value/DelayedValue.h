#ifndef ANCE_SRC_ANCE_CONSTRUCT_VALUE_DELAYEDVALUE_H_
#define ANCE_SRC_ANCE_CONSTRUCT_VALUE_DELAYEDVALUE_H_

#include "Value.h"

class DelayableExpression;

namespace ance
{
class DelayedValue : public Value
{
	public:
		explicit DelayedValue(DelayableExpression* expression);

		ance::Type* getType() override;

		void setValue(ance::Value* value);

		void buildNativeValue(CompileContext* context) override;

		llvm::Value* getNativeValue() override;

	private:
		DelayableExpression* expression_;
		ance::Value* value_{nullptr};
};
}

#endif
