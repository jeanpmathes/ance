#include "WrappedContentValue.h"

#include <utility>

#include "compiler/CompileContext.h"

lang::WrappedContentValue::WrappedContentValue(lang::ResolvingHandle<lang::Type> type) : type_(std::move(type)) {}

lang::WrappedContentValue::WrappedContentValue(lang::ResolvingHandle<lang::Type> type,
                                               llvm::Value*                      value,
                                               CompileContext&                   context)
    : type_(std::move(type))
{
    content_value_ = value;

    llvm::Type* llvm_type = context.exec().llvmType(type_);
    assert(content_value_->getType() == llvm_type);
}

void lang::WrappedContentValue::setValue(llvm::Value* value, CompileContext& context)
{
    assert(content_value_ == nullptr);

    llvm::Type* llvm_type = context.exec().llvmType(type_);
    assert(content_value_->getType() == llvm_type);

    content_value_ = value;
}

lang::ResolvingHandle<lang::Type> lang::WrappedContentValue::type()
{
    return type_;
}

lang::Type const& lang::WrappedContentValue::type() const
{
    return type_;
}

void lang::WrappedContentValue::buildContentValue(CompileContext&) {}
