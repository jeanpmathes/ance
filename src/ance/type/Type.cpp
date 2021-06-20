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

llvm::TypeSize ance::Type::getNativeSize(llvm::Module* m)
{
	return m->getDataLayout().getTypeAllocSize(getNativeType(m->getContext()));
}

llvm::TypeSize ance::Type::getContentSize(llvm::Module* m)
{
	return m->getDataLayout().getTypeAllocSize(getContentType(m->getContext()));
}

bool ance::Type::isIndexerDefined(Indexer)
{
	return false;
}

InternalStorage ance::Type::storage()
{
	return InternalStorage::AS_TEMPORARY;
}

ance::Type* ance::Type::getIndexerReturnType()
{
	return nullptr;
}

ance::Value* ance::Type::buildGetIndexer(
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

void ance::Type::buildSetIndexer(
	ance::Value*,
	ance::Value*,
	ance::Value*,
	llvm::LLVMContext&,
	llvm::Module*,
	CompileState*,
	llvm::IRBuilder<>&,
	llvm::DIBuilder*
)
{

}
