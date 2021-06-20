#include "DelayableExpression.h"

ance::Value* DelayableExpression::getValue()
{
	return value_;
}

void DelayableExpression::build(
	llvm::LLVMContext& c,
	llvm::Module* m,
	CompileState* state,
	llvm::IRBuilder<>& ir,
	llvm::DIBuilder* di
)
{
	buildValue(c, m, state, ir, di);
}

void DelayableExpression::setValue(ance::Value* value)
{
	value_->setValue(value);
}
