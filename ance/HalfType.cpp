#include "HalfType.h"

#include <llvm/IR/Constants.h>

#include "GlobalScope.h"
#include "Scope.h"

std::string ance::HalfType::get_name()
{
	return "half";
}

llvm::Constant* ance::HalfType::get_default(llvm::LLVMContext& c)
{
	return llvm::ConstantFP::get(get_native_type(c), 0);
}

llvm::Type* ance::HalfType::get_native_type(llvm::LLVMContext& c)
{
	return llvm::Type::getHalfTy(c);
}

ance::FloatingPointType* ance::HalfType::get(ance::Scope* scope)
{
	if (!instance)
	{
		instance = new HalfType();
		scope->get_global_scope()->register_type(instance);
	}

	return instance;
}