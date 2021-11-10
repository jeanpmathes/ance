#include "WrappedNativeValue.h"

ance::WrappedNativeValue::WrappedNativeValue(ance::ResolvingHandle<ance::Type> type, llvm::Value* value)
    : type_(type)
    , value_(value)
{}

void ance::WrappedNativeValue::setValue(llvm::Value* value)
{
    value_ = value;
}

ance::ResolvingHandle<ance::Type> ance::WrappedNativeValue::type()
{
    return type_;
}

void ance::WrappedNativeValue::buildNativeValue(CompileContext*) {}

llvm::Value* ance::WrappedNativeValue::getNativeValue()
{
    return value_;
}
