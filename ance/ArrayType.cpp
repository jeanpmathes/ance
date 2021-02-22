#include "ArrayType.h"
#include "Scope.h"

#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>

#include "GlobalScope.h"

ance::ArrayType::ArrayType(Type* element_type, const uint64_t size) :
	size_(size),
	element_type_(element_type),
	type_(nullptr)
{
}

std::string ance::ArrayType::get_name()
{
	return element_type_->get_name() + "[" + std::to_string(size_) + "]";
}

llvm::Constant* ance::ArrayType::get_default(llvm::LLVMContext& c)
{
	llvm::Constant* consts[size_];
	std::fill_n(consts, size_, element_type_->get_default(c));

	if (!type_) get_native_type(c);

	llvm::ArrayRef<llvm::Constant*> content = llvm::ArrayRef<llvm::Constant*>(&consts[0], size_);

	return llvm::ConstantArray::get(type_, content);
}

llvm::Type* ance::ArrayType::get_native_type(llvm::LLVMContext& c)
{
	if (!type_)
	{
		type_ = llvm::ArrayType::get(element_type_->get_native_type(c), size_);
	}

	return type_;
}

ance::Type* ance::ArrayType::get(ance::Scope* scope, Type* element_type, uint64_t size)
{
	ance::ArrayType* type = new ance::ArrayType(element_type, size);
	std::string type_name = type->get_name();

	if (scope->get_global_scope()->is_type_registered(type_name))
	{
		delete type;
		return scope->get_global_scope()->get_type(type_name);
	}
	else
	{
		scope->get_global_scope()->register_type(type);
		return type;
	}
}