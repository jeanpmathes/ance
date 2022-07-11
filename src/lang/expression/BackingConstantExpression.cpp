#include "BackingConstantExpression.h"

#include "lang/construct/constant/Constant.h"
#include "compiler/CompileContext.h"

void BackingConstantExpression::buildConstant(llvm::Module& m)
{
    assert(!content_constant_ && "Content may only be built once.");
    content_constant_ = buildContentConstant(m);
}

llvm::Constant* BackingConstantExpression::getContentConstant()
{
    assert(content_constant_ && "Content must be build before usage.");
    return content_constant_;
}

void BackingConstantExpression::doBuild(CompileContext*) {}
