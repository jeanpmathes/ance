#include "Values.h"

#include "Value.h"
#include "Type.h"
#include "CompileState.h"

llvm::Value* ance::Values::nativeToContent(
	ance::Type* type,
	llvm::Value* native,
	llvm::LLVMContext& c,
	llvm::Module*,
	CompileState*,
	llvm::IRBuilder<>& ir,
	llvm::DIBuilder*
)
{
	switch (type->storage())
	{
		case InternalStorage::AS_TEMPORARY:
		{
			return native;
		}
		case InternalStorage::AS_POINTER:
		{
			return ir.CreateLoad(native);
		}
	}
}

llvm::Value* ance::Values::contentToNative(
	ance::Type* type,
	llvm::Value* content,
	llvm::LLVMContext& c,
	llvm::Module*,
	CompileState*,
	llvm::IRBuilder<>& ir,
	llvm::DIBuilder*
)
{
	switch (type->storage())
	{
		case InternalStorage::AS_TEMPORARY:
		{
			return content;
		}
		case InternalStorage::AS_POINTER:
		{
			llvm::Value* native = ir.CreateAlloca(type->getContentType(c));
			ir.CreateStore(content, native);
			return native;
		}
	}
}
