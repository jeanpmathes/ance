#include "QuadType.h"

#include <llvm/IR/Constants.h>

#include "GlobalScope.h"
#include "Scope.h"

std::string ance::QuadType::get_name()
{
	return "quad";
}

llvm::Constant* ance::QuadType::get_default(llvm::LLVMContext& c)
{
	return llvm::ConstantFP::get(get_native_type(c), 0);
}

llvm::Type* ance::QuadType::get_native_type(llvm::LLVMContext& c)
{
	return llvm::Type::getFP128Ty(c);
}

ance::FloatingPointType* ance::QuadType::get(ance::Scope* scope)
{
	if (!instance)
	{
		instance = new QuadType();
		scope->get_global_scope()->register_type(instance);
	}

	return instance;
}