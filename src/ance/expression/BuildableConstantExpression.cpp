#include "BuildableConstantExpression.h"

#include "Constant.h"
#include "Values.h"

void BuildableConstantExpression::buildConstant(llvm::LLVMContext& c)
{
	assert(!content_constant_ && "Content may only be built once.");
	content_constant_ = buildContentConstant(c);
}

llvm::Constant* BuildableConstantExpression::getContentConstant()
{
	assert(content_constant_ && "Content must be build before usage.");
	return content_constant_;
}

llvm::Value* BuildableConstantExpression::buildNativeValue(
	llvm::LLVMContext& c,
	llvm::Module* m,
	CompileState* state,
	llvm::IRBuilder<>& ir,
	llvm::DIBuilder* di
)
{
	buildConstant(c);
	return ance::Values::contentToNative(getType(), content_constant_, c, m, state, ir, di);
}
