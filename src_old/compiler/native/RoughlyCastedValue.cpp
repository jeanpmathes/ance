#include "RoughlyCastedValue.h"

#include "NativeBuild.h"

RoughlyCastedValue::RoughlyCastedValue(lang::Type const&   target_type,
                                       Shared<lang::Value> original,
                                       NativeBuild&        native_build)
    : lang::Value(target_type)
    , original_(std::move(original))
{
    assert(native_build.llvmType(target_type) == native_build.llvmType(original_->type()));
}

llvm::Value* RoughlyCastedValue::getNativeValue() const
{
    return original_.cast<Wrapped>().getNativeValue();
}

llvm::Value* RoughlyCastedValue::getContentValue() const
{
    return original_.cast<Wrapped>().getContentValue();
}

llvm::Constant* RoughlyCastedValue::getConstant() const
{
    return original_.cast<Wrapped>().getConstant();
}
