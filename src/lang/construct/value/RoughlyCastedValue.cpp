#include "RoughlyCastedValue.h"

#include <utility>

#include "lang/type/Type.h"
#include "compiler/CompileContext.h"

lang::RoughlyCastedValue::RoughlyCastedValue(lang::ResolvingHandle<lang::Type> target_type,
                                             std::shared_ptr<lang::Value>      original)
    : target_type_(target_type)
    , original_(std::move(original))
{}

lang::ResolvingHandle<lang::Type> lang::RoughlyCastedValue::type() const
{
    return target_type_;
}

void lang::RoughlyCastedValue::buildNativeValue(CompileContext& context)
{
    assert(target_type_->getNativeType(*context.llvmContext())
               == original_->type()->getNativeType(*context.llvmContext())
           && "Native type has to be equal.");

    original_->buildNativeValue(context);
}

llvm::Value* lang::RoughlyCastedValue::getNativeValue()
{
    return original_->getNativeValue();
}
