#include "SingleType.h"

#include <llvm/IR/Constants.h>

#include "GlobalScope.h"
#include "Scope.h"

std::string ance::SingleType::get_name()
{
	return "single";
}

llvm::Constant* ance::SingleType::get_default(llvm::LLVMContext& c)
{
	return llvm::ConstantFP::get(get_native_type(c), 0);
}

llvm::Type* ance::SingleType::get_native_type(llvm::LLVMContext& c)
{
	return llvm::Type::getFloatTy(c);
}

ance::FloatingPointType* ance::SingleType::get(ance::Scope* scope)
{
	if (!instance)
	{
		instance = new SingleType();
		scope->get_global_scope()->register_type(instance);
	}

	return instance;
}