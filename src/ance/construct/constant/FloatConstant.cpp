#include "FloatConstant.h"

#include "ance/type/FloatingPointType.h"

ance::FloatConstant::FloatConstant(llvm::APFloat number, ance::FloatingPointType* type)
    : type_(type)
    , float_(std::move(number))
{}

ance::Type* ance::FloatConstant::type()
{
    return type_;
}

llvm::Constant* ance::FloatConstant::buildContent(llvm::Module* m)
{
    return llvm::ConstantFP::get(type_->getContentType(m->getContext()), float_);
}