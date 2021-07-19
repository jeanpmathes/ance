#include "SizeofType.h"

#include "compiler/CompileContext.h"
#include "ance/type/SizeType.h"

SizeofType::SizeofType(ance::Type* type)
    : type_(type)
{
}

ance::Type* SizeofType::type()
{
    return ance::SizeType::get();
}

ance::Value* SizeofType::getValue()
{
    return return_value_;
}

llvm::Value* SizeofType::buildNativeValue(CompileContext* context)
{
    return ance::SizeType::buildValue(type_->getContentSize(context->module()));
}