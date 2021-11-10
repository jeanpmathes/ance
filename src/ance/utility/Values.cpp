#include "Values.h"

#include "ance/construct/value/Value.h"
#include "compiler/CompileContext.h"

llvm::Value* ance::Values::nativeToContent(ance::ResolvingHandle<ance::Type>,
                                           llvm::Value*    native,
                                           CompileContext* context)
{
    llvm::Value* content = context->ir()->CreateLoad(native);
    return content;
}

llvm::Value* ance::Values::contentToNative(ance::ResolvingHandle<ance::Type> type,
                                           llvm::Value*                      content,
                                           CompileContext*                   context)
{
    llvm::Value* native = context->ir()->CreateAlloca(type->getContentType(*context->llvmContext()));
    context->ir()->CreateStore(content, native);
    return native;
}
