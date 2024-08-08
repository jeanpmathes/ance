#include "WrappedContentValue.h"

#include "NativeBuild.h"

WrappedContentValue::WrappedContentValue(lang::Type const& type, llvm::Value* value) : Value(type), value_(value) {}

llvm::Value* WrappedContentValue::getContentValue() const
{
    return value_;
}
