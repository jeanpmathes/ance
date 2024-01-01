#include "Constant.h"

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/type/Type.h"

Expression* lang::Constant::getBackingExpression() const
{
    return nullptr;
}

bool lang::Constant::validate(ValidationLogger&, lang::Location) const
{
    return true;
}

void lang::Constant::buildContentConstant(CompileContext& context)
{
    if (content_constant_) return;
    content_constant_ = createContent(context);
}

llvm::Constant* lang::Constant::getContentConstant()
{
    assert(content_constant_);
    return content_constant_;
}

void lang::Constant::buildContentValue(CompileContext& context)
{
    buildContentConstant(context);
    content_value_ = content_constant_;
}
