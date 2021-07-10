#include "Value.h"

#include "Values.h"

void ance::Value::buildContentValue(
	llvm::LLVMContext& c,
	llvm::Module* m,
	CompileContext* state,
	llvm::IRBuilder<>& ir,
	llvm::DIBuilder* di
)
{
	buildNativeValue(c, m, state, ir, di);
	content_value_ = ance::Values::nativeToContent(getType(), getNativeValue(), c, m, state, ir, di);
}

llvm::Value* ance::Value::getContentValue()
{
	assert(content_value_ && "Content value must be built before accessing it.");
	return content_value_;
}
