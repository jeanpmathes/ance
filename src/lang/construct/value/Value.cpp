#include "Value.h"

#include "compiler/CompileContext.h"
#include "lang/type/Type.h"

void lang::Value::buildNativeValue(CompileContext& context)
{
    if (native_value_) return;
    buildContentValue(context);

    native_value_ = context.exec().ir().CreateAlloca(context.exec().llvmType(type()), nullptr, "store");
    context.exec().ir().CreateStore(getContentValue(), native_value_);
}

void lang::Value::buildContentValue(CompileContext& context)
{
    if (content_value_) return;
    buildNativeValue(context);

    content_value_ = context.exec().ir().CreateLoad(context.exec().llvmType(type()),
                                                    getNativeValue(),
                                                    getNativeValue()->getName() + ".load");
}

llvm::Value* lang::Value::getNativeValue() const
{
    assert(native_value_);
    return native_value_;
}

llvm::Value* lang::Value::getContentValue() const
{
    assert(content_value_);
    return content_value_;
}
