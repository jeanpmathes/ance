#include "WrappedNativeValue.h"

lang::WrappedNativeValue::WrappedNativeValue(lang::ResolvingHandle<lang::Type> type, llvm::Value* value)
    : type_(type)
    , value_(value)
{}

void lang::WrappedNativeValue::setValue(llvm::Value* value)
{
    value_ = value;
}

lang::ResolvingHandle<lang::Type> lang::WrappedNativeValue::type()
{
    return type_;
}

void lang::WrappedNativeValue::buildNativeValue(CompileContext*) {}

llvm::Value* lang::WrappedNativeValue::getNativeValue()
{
    return value_;
}
