#include "RoughlyCastedValue.h"

#include <utility>

#include "compiler/CompileContext.h"
#include "lang/type/Type.h"

lang::RoughlyCastedValue::RoughlyCastedValue(lang::ResolvingHandle<lang::Type> target_type,
                                             Shared<lang::Value>               original)
    : target_type_(std::move(target_type))
    , original_(std::move(original))
{}

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
    assert(target_type_->getNativeType(context.llvmContext()) == original_->type()->getNativeType(context.llvmContext())
           && "Native type has to be equal.");

    original_->buildNativeValue(context);
}

llvm::Value* lang::RoughlyCastedValue::getNativeValue() const
{
    return original_->getNativeValue();
}
