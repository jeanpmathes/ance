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
    assert(target_type_->getContentType(context) == original_->type()->getContentType(context));
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
    assert(target_type_->getNativeType(context) == original_->type()->getNativeType(context)
           && "Native type has to be equal.");

    original_->buildNativeValue(context);
    native_value_ = original_->getNativeValue();
}

void lang::RoughlyCastedValue::buildContentValue(CompileContext& context)
{
    assert(target_type_->getNativeType(context) == original_->type()->getNativeType(context)
           && "Native type has to be equal.");

    original_->buildContentValue(context);
    content_value_ = original_->getContentValue();
}
