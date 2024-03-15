#include "WrappedContentValue.h"

#include "NativeBuild.h"

WrappedContentValue::WrappedContentValue(lang::Type const& type, llvm::Value* value, NativeBuild& native_build)
    : Value(type)
    , native_build_(native_build)
    , value_(value)
{}

Execution::Handle<false> WrappedContentValue::getExecutionValue()
{
    return native_build_.allocateContentValue(value_);
}
