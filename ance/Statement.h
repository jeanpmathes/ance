#pragma once
#include "llvm/IR/IRBuilder.h"
class Statement
{
public:
	virtual void Build(llvm::LLVMContext& c, llvm::IRBuilder<>& ir) = 0;
	virtual ~Statement() = 0;
};
