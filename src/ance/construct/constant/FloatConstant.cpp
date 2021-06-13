#include "FloatConstant.h"

ance::FloatConstant::FloatConstant(llvm::APFloat number, ance::FloatingPointType* type)
	: type_(type), float_(std::move(number))
{
}

ance::Type* ance::FloatConstant::getType()
{
	return type_;
}

llvm::Constant* ance::FloatConstant::buildContent(llvm::Module* m)
{
	return llvm::ConstantFP::get(type_->getNativeType(m->getContext()), float_);
}