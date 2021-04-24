#include "SingleType.h"

#include <llvm/IR/Constants.h>

#include "GlobalScope.h"
#include "Scope.h"

std::string ance::SingleType::getName()
{
	return "single";
}

llvm::Constant* ance::SingleType::getDefault(llvm::LLVMContext& c)
{
	return llvm::ConstantFP::get(getNativeType(c), 0);
}

llvm::Type* ance::SingleType::getNativeType(llvm::LLVMContext& c)
{
	return llvm::Type::getFloatTy(c);
}

ance::FloatingPointType* ance::SingleType::get(ance::Scope* scope)
{
	if (!instance_)
	{
		instance_ = new SingleType();
		scope->getGlobalScope()->registerType(instance_);
	}

	return instance_;
}