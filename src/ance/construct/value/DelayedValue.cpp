#include "DelayedValue.h"

#include "DelayableExpression.h"

ance::DelayedValue::DelayedValue(DelayableExpression* expression)
	: expression_(expression)
{

}

ance::Type* ance::DelayedValue::getType()
{
	return expression_->getType();
}

void ance::DelayedValue::setValue(ance::Value* value)
{
	assert(!value_);
	assert(value->getType() == getType() && "Type has to match.");
	value_ = value;
}

void ance::DelayedValue::buildNativeValue(
	llvm::LLVMContext& c,
	llvm::Module* m,
	CompileState* state,
	llvm::IRBuilder<>& ir,
	llvm::DIBuilder* di
)
{
	expression_->buildValue(c, m, state, ir, di);
	value_->buildNativeValue(c, m, state, ir, di);
}

llvm::Value* ance::DelayedValue::getNativeValue()
{
	return value_->getNativeValue();
}
