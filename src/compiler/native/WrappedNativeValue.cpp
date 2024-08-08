#include "WrappedNativeValue.h"

WrappedNativeValue::WrappedNativeValue(lang::Type const& type, llvm::Value* value) : Value(type), value_(value) {}

llvm::Value* WrappedNativeValue::getNativeValue() const
{
    return value_;
}
