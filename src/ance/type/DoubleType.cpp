#include "DoubleType.h"

#include <llvm/IR/Constants.h>

#include "GlobalScope.h"
#include "Scope.h"

std::string ance::DoubleType::getName()
{
	return "double";
}

llvm::Constant* ance::DoubleType::getDefaultContent(llvm::LLVMContext& c)
{
	return llvm::ConstantFP::get(getNativeType(c), 0);
}

llvm::Type* ance::DoubleType::getContentType(llvm::LLVMContext& c)
{
	return llvm::Type::getDoubleTy(c);
}

ance::FloatingPointType* ance::DoubleType::get()
{
	if (!instance_)
	{
		instance_ = new DoubleType();
	}

	return instance_;
}