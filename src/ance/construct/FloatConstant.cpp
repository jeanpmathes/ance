#include "FloatConstant.h"

ance::FloatConstant::FloatConstant(llvm::APFloat number, ance::FloatingPointType* type)
    : type_(type), float_(std::move(number)), constant_(nullptr)
{
}

ance::Type* ance::FloatConstant::get_type()
{
    return type_;
}

llvm::Constant* ance::FloatConstant::get_constant(llvm::LLVMContext& c)
{
    if (!constant_)
    {
        constant_ = llvm::ConstantFP::get(type_->get_native_type(c), float_);
    }

    return constant_;
}
