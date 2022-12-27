#include "Values.h"

#include "compiler/CompileContext.h"
#include "lang/construct/value/Value.h"
#include "lang/construct/value/WrappedNativeValue.h"

llvm::Value* lang::values::nativeToContent(lang::Type const& type, llvm::Value* native, CompileContext& context)
{
    llvm::Value* content =
        context.ir()->CreateLoad(type.getContentType(*context.llvmContext()), native, native->getName() + ".load");
    return content;
}

llvm::Value* lang::values::contentToNative(lang::Type const& type, llvm::Value* content, CompileContext& context)
{
    llvm::Value* native = context.ir()->CreateAlloca(type.getContentType(*context.llvmContext()), nullptr, "alloca");

    context.ir()->CreateStore(content, native);
    return native;
}

Shared<lang::Value> lang::values::clone(Shared<lang::Value> value)
{
    llvm::Value* native = value->getNativeValue();
    return makeShared<lang::WrappedNativeValue>(value->type(), native);
}
