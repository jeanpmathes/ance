#include "SizeofType.h"

#include "ance/type/SizeType.h"
#include "compiler/CompileContext.h"

SizeofType::SizeofType(ance::Type* type, ance::Location location) : Expression(location), type_(type) {}

ance::Type* SizeofType::type()
{
    return ance::SizeType::get();
}

bool SizeofType::validate(ValidationLogger&)
{
    return true;
}

ance::Value* SizeofType::getValue() const
{
    return return_value_;
}

llvm::Value* SizeofType::buildNativeValue(CompileContext* context)
{
    return ance::SizeType::buildValue(type_->getContentSize(context->module()));
}
