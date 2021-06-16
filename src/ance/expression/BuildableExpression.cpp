#include "BuildableExpression.h"

void BuildableExpression::build(
	llvm::LLVMContext& c,
	llvm::Module* m,
	CompileState* state,
	llvm::IRBuilder<>& ir,
	llvm::DIBuilder* di
)
{
	assert(!native_value_ && "Expressions must be built only once.");
	native_value_ = buildNativeValue(c, m, state, ir, di);
}

llvm::Value* BuildableExpression::getNativeValue()
{
	assert(native_value_ && "Expressions must be built before accessing value.");
	return native_value_;
}

