#include "Values.h"

#include "compiler/CompileContext.h"
#include "lang/construct/value/Value.h"
#include "lang/construct/value/WrappedNativeValue.h"

llvm::Value* lang::Values::nativeToContent(lang::ResolvingHandle<lang::Type> type,
                                           llvm::Value*                      native,
                                           CompileContext&                   context)
{
    llvm::Value* content =
        context.ir()->CreateLoad(type->getContentType(*context.llvmContext()), native, native->getName() + ".load");
    return content;
}

llvm::Value* lang::Values::contentToNative(lang::ResolvingHandle<lang::Type> type,
                                           llvm::Value*                      content,
                                           CompileContext&                   context)
{
    llvm::Value* native = context.ir()->CreateAlloca(type->getContentType(*context.llvmContext()), nullptr, "alloca");

    context.ir()->CreateStore(content, native);
    return native;
}

std::shared_ptr<lang::Value> lang::Values::clone(const std::shared_ptr<lang::Value>& value)
{
    llvm::Value* native = value->getNativeValue();
    return std::make_shared<lang::WrappedNativeValue>(value->type(), native);
}

