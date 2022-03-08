#include "Constant.h"

#include "lang/type/Type.h"
#include "lang/utility/Values.h"

#include "compiler/CompileContext.h"

Expression* lang::Constant::getBackingExpression() const
{
    return nullptr;
}

bool lang::Constant::validate(ValidationLogger&, lang::Location)
{
    return true;
}

void lang::Constant::buildContentConstant(llvm::Module* m)
{
    assert(!content_constant_ && "A constant may only be built once.");
    content_constant_ = buildContent(m);
}

llvm::Constant* lang::Constant::getContentConstant()
{
    assert(content_constant_ && "Constant has to be built before accessing content constant.");
    return content_constant_;
}

void lang::Constant::buildNativeValue(CompileContext* context)
{
    buildContentConstant(context->module());
    native_value_ = lang::Values::contentToNative(type(), content_constant_, context);
}

void lang::Constant::buildContentValue(CompileContext* context)
{
    buildContentConstant(context->module());
}

llvm::Value* lang::Constant::getNativeValue()
{
    assert(native_value_ && "Value has to be built before accessing native value.");
    return native_value_;
}

llvm::Value* lang::Constant::getContentValue()
{
    assert(content_constant_ && "Value has to be built before accessing content value.");
    return content_constant_;
}
