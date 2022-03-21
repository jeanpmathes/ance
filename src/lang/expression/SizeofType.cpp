#include "SizeofType.h"

#include "lang/scope/Scope.h"
#include "lang/type/SizeType.h"
#include "compiler/CompileContext.h"
#include "validation/ValidationLogger.h"

SizeofType::SizeofType(lang::ResolvingHandle<lang::Type> type, lang::Location type_location, lang::Location location)
    : Expression(location)
    , type_(type)
    , type_location_(type_location)
{}

lang::ResolvingHandle<lang::Type> SizeofType::targetType() const
{
    return type_;
}

void SizeofType::setScope(lang::Scope*) {}

void SizeofType::walkDefinitions()
{
    scope()->addType(type_);
}

lang::ResolvingHandle<lang::Type> SizeofType::type()
{
    return lang::SizeType::getSize();
}

bool SizeofType::validate(ValidationLogger& validation_logger)
{
    if (!type_->isDefined())
    {
        validation_logger.logError("Type " + type_->getAnnotatedName() + " not defined", type_location_);
        return false;
    }

    return type_->validate(validation_logger, type_location_);
}

std::shared_ptr<lang::Value> SizeofType::getValue() const
{
    return return_value_;
}

llvm::Value* SizeofType::buildNativeValue(CompileContext* context)
{
    return lang::SizeType::buildValue(type_->getContentSize(context->module()));
}
