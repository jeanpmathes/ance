#include "DelayableExpression.h"

ance::Value* DelayableExpression::getValue()
{
	return value_;
}

void DelayableExpression::build(CompileContext* context)
{
	buildValue(context);
}

void DelayableExpression::setValue(ance::Value* value)
{
	value_->setValue(value);
}
