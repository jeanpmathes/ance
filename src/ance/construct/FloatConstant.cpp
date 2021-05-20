#include "FloatConstant.h"

ance::FloatConstant::FloatConstant(llvm::APFloat number, ance::FloatingPointType* type)
	: type_(type), float_(std::move(number))
{
}

ance::Type* ance::FloatConstant::getType()
{
	return type_;
}

void ance::FloatConstant::build(llvm::LLVMContext& c)
{
	assert(!constant_);
	constant_ = llvm::ConstantFP::get(type_->getNativeType(c), float_);
}

llvm::Constant * ance::FloatConstant::getNativeConstant()
{
	assert(constant_);
	return constant_;
}