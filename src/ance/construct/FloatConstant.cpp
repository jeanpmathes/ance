#include "FloatConstant.h"

ance::FloatConstant::FloatConstant(llvm::APFloat number, ance::FloatingPointType* type)
    : type_(type), float_(std::move(number))
{
}

ance::Type* ance::FloatConstant::getType()
{
    return type_;
}

llvm::Constant* ance::FloatConstant::getConstant(llvm::LLVMContext& c)
{
    if (!constant_)
    {
        constant_ = llvm::ConstantFP::get(type_->getNativeType(c), float_);
    }

    return constant_;
}
