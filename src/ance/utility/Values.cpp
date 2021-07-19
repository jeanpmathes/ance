#include "Values.h"

#include "compiler/CompileContext.h"
#include "ance/type/Type.h"
#include "ance/construct/value/Value.h"

llvm::Value* ance::Values::nativeToContent(ance::Type* type, llvm::Value* native, CompileContext* context)
{
    switch (type->storage())
    {
        case InternalStorage::AS_TEMPORARY: {
            return native;
        }
        case InternalStorage::AS_POINTER: {
            return context->ir()->CreateLoad(native);
        }
    }
}

llvm::Value* ance::Values::contentToNative(ance::Type* type, llvm::Value* content, CompileContext* context)
{
    switch (type->storage())
    {
        case InternalStorage::AS_TEMPORARY: {
            return content;
        }
        case InternalStorage::AS_POINTER: {
            llvm::Value* native = context->ir()->CreateAlloca(type->getContentType(*context->llvmContext()));
            context->ir()->CreateStore(content, native);
            return native;
        }
    }
}
