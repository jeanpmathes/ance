#include "SizeofType.h"

#include "ance/type/SizeType.h"
#include "ance/type/Type.h"
#include "compiler/CompileContext.h"

SizeofType::SizeofType(ance::ResolvingHandle<ance::Type> type, ance::Location type_location, ance::Location location)
    : Expression(location)
    , type_(type)
    , type_location_(type_location)
{}

ance::ResolvingHandle<ance::Type> SizeofType::type()
{
    return ance::SizeType::getSize();
}

bool SizeofType::validate(ValidationLogger& validation_logger)
{
    return type_->validate(validation_logger, type_location_);
}

std::shared_ptr<ance::Value> SizeofType::getValue() const
{
    return return_value_;
}

llvm::Value* SizeofType::buildNativeValue(CompileContext* context)
{
    return ance::SizeType::buildValue(type_->getContentSize(context->module()));
}
