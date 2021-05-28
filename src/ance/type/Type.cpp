#include "Type.h"

llvm::Type* ance::Type::getNativeType(llvm::LLVMContext& c)
{
	switch (storage())
	{
		case InternalStorage::AS_TEMPORARY:
		{
			return getContentType(c);
		}
		case InternalStorage::AS_POINTER:
		{
			return llvm::PointerType::get(getContentType(c), 0);
		}
	}
}

llvm::TypeSize ance::Type::getSize(llvm::Module* m)
{
	return m->getDataLayout().getTypeAllocSize(getNativeType(m->getContext()));
}

bool ance::Type::isIndexerDefined(Indexer)
{
	return false;
}

ance::Type* ance::Type::getIndexerReturnType()
{
	return nullptr;
}

llvm::Value* ance::Type::buildGetIndexer(
	ance::Value*,
	ance::Value*,
	llvm::LLVMContext&,
	llvm::Module*,
	CompileState*,
	llvm::IRBuilder<>&,
	llvm::DIBuilder*
)
{
	return nullptr;
}

InternalStorage ance::Type::storage()
{
	return InternalStorage::AS_TEMPORARY;
}
