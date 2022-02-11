#include "BackingConstantExpression.h"

#include "lang/construct/constant/Constant.h"
#include "lang/utility/Values.h"
#include "compiler/CompileContext.h"

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
    return lang::Values::contentToNative(type(), content_constant_, context);
}
