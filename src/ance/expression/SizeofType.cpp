#include "SizeofType.h"

#include "ance/ApplicationVisitor.h"
#include "ance/type/SizeType.h"
#include "compiler/CompileContext.h"

SizeofType::SizeofType(ance::Type* type, ance::Location location) : Expression(location), type_(type) {}

ance::Type* SizeofType::type()
{
    return ance::SizeType::getSize();
}

bool SizeofType::validate(ValidationLogger& validation_logger)
{
    return type_->validate(validation_logger, location());
}

ance::Value* SizeofType::getValue() const
{
    return return_value_;
}

llvm::Value* SizeofType::buildNativeValue(CompileContext* context)
{
    return ance::SizeType::buildValue(type_->getContentSize(context->module()));
}

bool SizeofType::accept(ance::ApplicationVisitor& visitor)
{
    return visitor.visitSizeofType(*this);
}
