#include "QuadType.h"

#include <llvm/IR/Constants.h>

#include "GlobalScope.h"
#include "Scope.h"

std::string ance::QuadType::getName()
{
	return "quad";
}

llvm::Constant* ance::QuadType::getDefault(llvm::LLVMContext& c)
{
	return llvm::ConstantFP::get(getNativeType(c), 0);
}

llvm::Type* ance::QuadType::getNativeType(llvm::LLVMContext& c)
{
	return llvm::Type::getFP128Ty(c);
}

ance::FloatingPointType* ance::QuadType::get()
{
	if (!instance_)
	{
		instance_ = new QuadType();
	}

	return instance_;
}