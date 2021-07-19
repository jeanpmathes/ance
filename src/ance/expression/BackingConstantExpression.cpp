#include "BackingConstantExpression.h"

#include "compiler/CompileContext.h"
#include "ance/construct/constant/Constant.h"
#include "ance/utility/Values.h"

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
    return ance::Values::contentToNative(type(), content_constant_, context);
}
