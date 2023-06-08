#include "WrappedNativeValue.h"

#include <utility>

#include "compiler/CompileContext.h"
#include "lang/utility/Values.h"

lang::WrappedNativeValue::WrappedNativeValue(lang::ResolvingHandle<lang::Type> type, llvm::Value* value)
    : type_(std::move(type))
    , value_(value)
{}

Shared<lang::Value> lang::WrappedNativeValue::makeDefault(lang::ResolvingHandle<lang::Type> type,
                                                          CompileContext&                   context)
{
    llvm::Value* content_value = type->getDefaultContent(context.llvmModule());
    llvm::Value* native_value  = lang::values::contentToNative(type, content_value, context);

    return makeShared<WrappedNativeValue>(type, native_value);
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
    assert(value_);
    return value_;
}
