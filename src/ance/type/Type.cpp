#include "Type.h"

llvm::TypeSize ance::Type::getSize(llvm::Module* m)
{
	return m->getDataLayout().getTypeAllocSize(getNativeType(m->getContext()));
}

InternalStorage ance::Type::storage()
{
	return InternalStorage::AS_TEMPORARY;
}
