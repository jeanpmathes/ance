#include "WrappedNativeConstant.h"

ance::WrappedNativeConstant::WrappedNativeConstant(ance::Type* type, llvm::Constant* constant) : type_(type), constant_(constant) {

}
void ance::WrappedNativeConstant::set_constant(llvm::Constant *constant) {
    constant_ = constant;
}
ance::Type *ance::WrappedNativeConstant::get_type() {
    return type_;
}
llvm::Constant *ance::WrappedNativeConstant::get_constant(llvm::LLVMContext &c) {
    return constant_;
}
