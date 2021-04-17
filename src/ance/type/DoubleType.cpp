#include "DoubleType.h"

#include <llvm/IR/Constants.h>

#include "GlobalScope.h"
#include "Scope.h"

std::string ance::DoubleType::getName()
{
	return "double";
}

llvm::Constant* ance::DoubleType::getDefault(llvm::LLVMContext& c)
{
	return llvm::ConstantFP::get(getNativeType(c), 0);
}

llvm::Type* ance::DoubleType::getNativeType(llvm::LLVMContext& c)
{
	return llvm::Type::getDoubleTy(c);
}

ance::FloatingPointType* ance::DoubleType::get(ance::Scope* scope)
{
	if (!instance_)
	{
        instance_ = new DoubleType();
        scope->getGlobalScope()->registerType(instance_);
	}

	return instance_;
}