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
    if (backing_constant_.hasValue()) return;
    if (getWrappedConstant() != nullptr) return;

    backing_constant_ = createContent(context);
    backing_constant_.value()->buildContentConstant(context);
}

llvm::Constant* lang::Constant::getWrappedConstant() const
{
    return nullptr;
}

llvm::Constant* lang::Constant::getContentConstant()
{
    if (getWrappedConstant() != nullptr) return getWrappedConstant();

    return backing_constant_.value()->getContentConstant();
}

void lang::Constant::buildContentValue(CompileContext& context)
{
    buildContentConstant(context);
    content_value_ = getContentConstant();
}
