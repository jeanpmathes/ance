#include "Value.h"

#include "Type.h"

llvm::Value* ance::Value::getContentValue(
	llvm::LLVMContext& c,
	llvm::Module* m,
	CompileState* state,
	llvm::IRBuilder<>& ir,
	llvm::DIBuilder* di
)
{
	switch (getType()->storage())
	{
		case InternalStorage::AS_TEMPORARY:
		{
			return getNativeValue();
		}

		case InternalStorage::AS_POINTER:
		{
			return ir.CreateLoad(getNativeValue());
		}
	}
}
