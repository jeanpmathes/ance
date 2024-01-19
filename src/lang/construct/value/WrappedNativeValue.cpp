#include "WrappedNativeValue.h"

#include <utility>

#include "compiler/CompileContext.h"

lang::WrappedNativeValue::WrappedNativeValue(lang::ResolvingHandle<lang::Type> type) : type_(std::move(type))
{}

lang::WrappedNativeValue::WrappedNativeValue(lang::ResolvingHandle<lang::Type> type,
                                             llvm::Value*                      value,
                                             CompileContext&)
    : type_(std::move(type))
{
    native_value_ = value;
    assert(native_value_->getType()->isPointerTy());
}

void lang::WrappedNativeValue::setValue(llvm::Value* value, CompileContext&)
{
    assert(native_value_ == nullptr);
    assert(value->getType()->isPointerTy());

    native_value_ = value;
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
