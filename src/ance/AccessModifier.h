#ifndef ACCESS_MODIFIER_H
#define ACCESS_MODIFIER_H

#include <llvm/IR/GlobalValue.h>

enum class AccessModifier
{
		PUBLIC_ACCESS, PRIVATE_ACCESS
};

llvm::GlobalValue::LinkageTypes Convert(AccessModifier access);

#endif