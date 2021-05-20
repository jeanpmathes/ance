#include "Value.h"

#include "Type.h"

llvm::Value* ance::Value::getStoredValue(
	llvm::LLVMContext&,
	llvm::Module*,
	CompileState*,
	llvm::IRBuilder<>& ir,
	llvm::DIBuilder*
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
