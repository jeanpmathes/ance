#include "PointerType.h"

#include <llvm/IR/Constants.h>

#include "Application.h"
#include "GlobalScope.h"

ance::PointerType::PointerType(ance::Type* element_type) : element_type_(element_type)
{

}

std::string ance::PointerType::getName()
{
	return element_type_->getName() + "*";
}

llvm::Constant* ance::PointerType::getDefault(llvm::LLVMContext& c)
{
	return llvm::ConstantPointerNull::get(getNativeType(c));
}

llvm::PointerType* ance::PointerType::getNativeType(llvm::LLVMContext& c)
{
	return llvm::PointerType::get(element_type_->getNativeType(c), 0);
}

ance::Type* ance::PointerType::get(Application& app, ance::Type* element_type)
{
	auto* type = new ance::PointerType(element_type);
	std::string type_name = type->getName();

	if (app.globalScope()->isTypeRegistered(type_name))
	{
		delete type;
		return app.globalScope()->getType(type_name);
	}
	else
	{
		app.globalScope()->registerType(type);
		return type;
	}
}
