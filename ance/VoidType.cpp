#include "VoidType.h"

#include <stdexcept>
#include <llvm/IR/Type.h>

std::string ance::VoidType::get_name()
{
	return "void";
}

llvm::Constant* ance::VoidType::get_default(llvm::LLVMContext& c)
{
	throw std::logic_error("Void does not have a default value.");
}

llvm::Type* ance::VoidType::get_native_type(llvm::LLVMContext& c)
{
	return llvm::Type::getVoidTy(c);
}

ance::VoidType* ance::VoidType::instance_ = new ance::VoidType();

ance::VoidType* ance::VoidType::get()
{
	return instance_;
}