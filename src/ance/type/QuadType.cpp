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

ance::FloatingPointType* ance::QuadType::get(ance::Scope* scope)
{
	if (!instance_)
	{
		instance_ = new QuadType();
		scope->getGlobalScope()->registerType(instance_);
	}

	return instance_;
}