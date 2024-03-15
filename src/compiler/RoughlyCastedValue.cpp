#include "RoughlyCastedValue.h"

#include "NativeBuild.h"

RoughlyCastedValue::RoughlyCastedValue(lang::Type const&   target_type,
                                       Shared<lang::Value> original,
                                       NativeBuild&        native_build)
    : Value(target_type)
    , original_(std::move(original))
{
    assert(native_build.llvmType(target_type) == native_build.llvmType(original_->type()));
}

Execution::Handle<false> RoughlyCastedValue::getExecutionValue()
{
    return original_->getExecutionValue();
}
