#include "SizeofType.h"

#include "lang/scope/Scope.h"
#include "lang/type/SizeType.h"
#include "compiler/CompileContext.h"
#include "validation/ValidationLogger.h"
#include "lang/statement/Statement.h"
#include "lang/utility/Values.h"
#include "lang/construct/value/WrappedNativeValue.h"

SizeofType::SizeofType(lang::ResolvingHandle<lang::Type> type, lang::Location type_location, lang::Location location)
    : Expression(location)
    , type_(type)
    , type_location_(type_location)
{}

lang::ResolvingHandle<lang::Type> SizeofType::targetType() const
{
    return type_;
}

void SizeofType::walkDefinitions()
{
    scope()->addType(type_);
}

lang::ResolvingHandle<lang::Type> SizeofType::type() const
{
    return lang::SizeType::getSize();
}

bool SizeofType::validate(ValidationLogger& validation_logger) const
{
    if (!type_->isDefined())
    {
        validation_logger.logError("Type " + type_->getAnnotatedName() + " not defined", type_location_);
        return false;
    }

    return type_->validate(validation_logger, type_location_);
}

Expression::Expansion SizeofType::expandWith(Expressions) const
{
    return {Statements(), std::make_unique<SizeofType>(type_->toUndefined(), type_location_, location()), Statements()};
}

void SizeofType::doBuild(CompileContext* context)
{
    llvm::Value* content_value = lang::SizeType::buildContentValue(type_->getContentSize(context->module()));
    llvm::Value* native_value  = lang::Values::contentToNative(type(), content_value, context);

    std::shared_ptr<lang::WrappedNativeValue> value = std::make_shared<lang::WrappedNativeValue>(type(), native_value);
    setValue(value);
}