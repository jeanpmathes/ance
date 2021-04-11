#ifndef ACCESS_MODIFIER_H
#define ACCESS_MODIFIER_H
#include <llvm/IR/GlobalValue.h>

enum class access_modifier { public_access, private_access };

llvm::GlobalValue::LinkageTypes convert(access_modifier access);

#endif