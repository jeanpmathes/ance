#include "BackingConstantExpression.h"

#include "CompileContext.h"
#include "Constant.h"
#include "Values.h"

void BackingConstantExpression::buildConstant(llvm::LLVMContext& c)
{
    assert(!content_constant_ && "Content may only be built once.");
    content_constant_ = buildContentConstant(c);
}

llvm::Constant* BackingConstantExpression::getContentConstant()
{
    assert(content_constant_ && "Content must be build before usage.");
    return content_constant_;
}

llvm::Value* BackingConstantExpression::buildNativeValue(CompileContext* context)
{
    buildConstant(*context->llvmContext());
    return ance::Values::contentToNative(getType(), content_constant_, context);
}
