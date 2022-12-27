#include "WrappedNativeValue.h"

#include <utility>

lang::WrappedNativeValue::WrappedNativeValue(lang::ResolvingHandle<lang::Type> type, llvm::Value* value)
    : type_(std::move(type))
    , value_(value)
{
    assert(value_);
}

void lang::WrappedNativeValue::setValue(llvm::Value* value)
{
    value_ = value;
}

lang::ResolvingHandle<lang::Type> lang::WrappedNativeValue::type()
{
    return type_;
}

lang::Type const& lang::WrappedNativeValue::type() const
{
    return type_;
}

void lang::WrappedNativeValue::buildNativeValue(CompileContext&) {}

llvm::Value* lang::WrappedNativeValue::getNativeValue() const
{
    return value_;
}
