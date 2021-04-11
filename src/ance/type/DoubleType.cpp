#include "DoubleType.h"

#include <llvm/IR/Constants.h>

#include "GlobalScope.h"
#include "Scope.h"

std::string ance::DoubleType::get_name()
{
	return "double";
}

llvm::Constant* ance::DoubleType::get_default(llvm::LLVMContext& c)
{
	return llvm::ConstantFP::get(get_native_type(c), 0);
}

llvm::Type* ance::DoubleType::get_native_type(llvm::LLVMContext& c)
{
	return llvm::Type::getDoubleTy(c);
}

ance::FloatingPointType* ance::DoubleType::get(ance::Scope* scope)
{
	if (!instance)
	{
		instance = new DoubleType();
		scope->get_global_scope()->register_type(instance);
	}

	return instance;
}