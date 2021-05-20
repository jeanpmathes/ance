#include "WrappedNativeConstant.h"

ance::WrappedNativeConstant::WrappedNativeConstant(ance::Type* type, llvm::Constant* constant)
	: type_(type), constant_(constant)
{

}

void ance::WrappedNativeConstant::setNativeConstant(llvm::Constant* constant)
{
	constant_ = constant;
}

ance::Type* ance::WrappedNativeConstant::getType()
{
	return type_;
}

void ance::WrappedNativeConstant::build(llvm::LLVMContext&)
{
}

llvm::Constant * ance::WrappedNativeConstant::getNativeConstant()
{
	return constant_;
}
