#include "Values.h"

#include "lang/construct/value/Value.h"
#include "compiler/CompileContext.h"

llvm::Value* lang::Values::nativeToContent(lang::ResolvingHandle<lang::Type>,
                                           llvm::Value*    native,
                                           CompileContext* context)
{
    llvm::Value* content = context->ir()->CreateLoad(native);
    return content;
}

llvm::Value* lang::Values::contentToNative(lang::ResolvingHandle<lang::Type> type,
                                           llvm::Value*                      content,
                                           CompileContext*                   context)
{
    llvm::Value* native = context->ir()->CreateAlloca(type->getContentType(*context->llvmContext()));
    context->ir()->CreateStore(content, native);
    return native;
}
