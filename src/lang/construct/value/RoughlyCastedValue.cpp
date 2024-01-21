#include "RoughlyCastedValue.h"

#include <utility>

#include "compiler/CompileContext.h"
#include "lang/type/Type.h"

lang::RoughlyCastedValue::RoughlyCastedValue(lang::ResolvingHandle<lang::Type> target_type,
                                             Shared<lang::Value>               original,
                                             CompileContext&                   context)
    : target_type_(std::move(target_type))
    , original_(std::move(original))
{
    llvm::Type* target_llvm_type   = context.exec().llvmType(target_type_);
    llvm::Type* original_llvm_type = context.exec().llvmType(original_->type());

    assert(target_llvm_type == original_llvm_type);
}

lang::ResolvingHandle<lang::Type> lang::RoughlyCastedValue::type()
{
    return target_type_;
}

lang::Type const& lang::RoughlyCastedValue::type() const
{
    return target_type_;
}

void lang::RoughlyCastedValue::buildNativeValue(CompileContext& context)
{
    llvm::Type* target_llvm_type   = context.exec().llvmType(target_type_);
    llvm::Type* original_llvm_type = context.exec().llvmType(original_->type());

    assert(target_llvm_type == original_llvm_type);

    original_->buildNativeValue(context);
    native_value_ = original_->getNativeValue();
}

void lang::RoughlyCastedValue::buildContentValue(CompileContext& context)
{
    llvm::Type* target_llvm_type   = context.exec().llvmType(target_type_);
    llvm::Type* original_llvm_type = context.exec().llvmType(original_->type());

    assert(target_llvm_type == original_llvm_type);

    original_->buildContentValue(context);
    content_value_ = original_->getContentValue();
}
