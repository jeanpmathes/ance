#include "SizeType.h"

#include <llvm/IR/Constants.h>

#include "Application.h"
#include "GlobalScope.h"

std::string ance::SizeType::getName()
{
	return "size";
}

llvm::Constant* ance::SizeType::getDefault(llvm::LLVMContext& c)
{
	return llvm::ConstantInt::get(getNativeType(c), 0, false);
}

llvm::Type* ance::SizeType::getNativeType(llvm::LLVMContext&)
{
	return native_type_;
}

llvm::Value* ance::SizeType::buildValue(llvm::TypeSize size)
{
	return llvm::ConstantInt::get(native_type_, size.getFixedSize(), false);
}

void ance::SizeType::init(llvm::LLVMContext& c, Application& app)
{
	assert(!native_type_);
	native_type_ = llvm::Type::getIntNTy(c, app.getBitness());
}

ance::SizeType* ance::SizeType::get(Application& app)
{
	if (!instance_)
	{
		instance_ = new SizeType();
		app.globalScope()->registerType(instance_);
	}

	return instance_;
}