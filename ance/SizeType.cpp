#include "SizeType.h"

#include <llvm/IR/Constants.h>

#include "Application.h"
#include "GlobalScope.h"

std::string ance::SizeType::get_name()
{
	return "size";
}

llvm::Constant* ance::SizeType::get_default(llvm::LLVMContext& c)
{
	return llvm::ConstantInt::get(get_native_type(c), 0, false);
}

llvm::Type* ance::SizeType::get_native_type(llvm::LLVMContext& c)
{
	return native_type_;
}

llvm::Value* ance::SizeType::build_value(llvm::TypeSize size)
{
	return llvm::ConstantInt::get(native_type_, size.getFixedSize(), false);
}

void ance::SizeType::init(llvm::LLVMContext& c, Application& app)
{
	assert(!native_type_);
	native_type_ = llvm::Type::getIntNTy(c, app.get_bitness());
}

ance::SizeType* ance::SizeType::get(Application& app)
{
	if (!instance)
	{
		instance = new SizeType();
		app.global_scope()->register_type(instance);
	}

	return instance;
}