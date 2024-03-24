#include "WrappedNativeValue.h"

#include <utility>

#include "compiler/NativeBuild.h"

WrappedNativeValue::WrappedNativeValue(lang::Type const& type, llvm::Value* value, NativeBuild& native_build)
    : Value(type)
    , native_build_(native_build)
    , value_(value)
{}

Execution::Handle<false> WrappedNativeValue::getExecutionValue()
{
    return native_build_.allocateNativeValue(value_);
}
