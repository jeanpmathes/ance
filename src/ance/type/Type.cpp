#include "Type.h"

llvm::TypeSize ance::Type::getSize(llvm::Module* m)
{
	return m->getDataLayout().getTypeAllocSize(getNativeType(m->getContext()));
}
