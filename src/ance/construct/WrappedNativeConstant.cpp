#include "WrappedNativeConstant.h"

ance::WrappedNativeConstant::WrappedNativeConstant(ance::Type* type, llvm::Constant* constant) : type_(type), constant_(constant) {

}
void ance::WrappedNativeConstant::setConstant(llvm::Constant *constant)
{
    constant_ = constant;
}

ance::Type *ance::WrappedNativeConstant::getType()
{
    return type_;
}

llvm::Constant *ance::WrappedNativeConstant::getConstant(llvm::LLVMContext&)
{
    return constant_;
}
