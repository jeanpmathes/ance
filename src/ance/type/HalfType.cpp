#include "HalfType.h"

#include <llvm/IR/Constants.h>

#include "GlobalScope.h"
#include "Scope.h"

std::string ance::HalfType::getName()
{
	return "half";
}

llvm::Constant* ance::HalfType::getDefault(llvm::LLVMContext& c)
{
	return llvm::ConstantFP::get(getNativeType(c), 0);
}

llvm::Type* ance::HalfType::getNativeType(llvm::LLVMContext& c)
{
	return llvm::Type::getHalfTy(c);
}

ance::FloatingPointType* ance::HalfType::get(ance::Scope* scope)
{
	if (!instance_)
	{
		instance_ = new HalfType();
		scope->getGlobalScope()->registerType(instance_);
	}

	return instance_;
}