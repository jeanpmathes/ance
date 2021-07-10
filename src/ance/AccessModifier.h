#ifndef ANCE_SRC_ANCE_ACCESSMODIFIER_H_
#define ANCE_SRC_ANCE_ACCESSMODIFIER_H_

#include <llvm/IR/GlobalValue.h>

enum class AccessModifier
{
    PUBLIC_ACCESS,
    PRIVATE_ACCESS
};

llvm::GlobalValue::LinkageTypes Convert(AccessModifier access);

#endif