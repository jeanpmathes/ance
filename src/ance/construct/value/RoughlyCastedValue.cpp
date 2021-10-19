#include "RoughlyCastedValue.h"

#include <utility>

#include "ance/type/Type.h"
#include "compiler/CompileContext.h"

ance::RoughlyCastedValue::RoughlyCastedValue(ance::Type* target_type, std::shared_ptr<ance::Value> original)
    : target_type_(target_type)
    , original_(std::move(original))
{}

ance::Type* ance::RoughlyCastedValue::type()
{
    return target_type_;
}

void ance::RoughlyCastedValue::buildNativeValue(CompileContext* context)
{
    assert(target_type_->getNativeType(*context->llvmContext())
               == original_->type()->getNativeType(*context->llvmContext())
           && "Native type has to be equal.");

    original_->buildNativeValue(context);
}

llvm::Value* ance::RoughlyCastedValue::getNativeValue()
{
    return original_->getNativeValue();
}
