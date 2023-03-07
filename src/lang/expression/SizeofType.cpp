#include "SizeofType.h"

#include <utility>

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/value/WrappedNativeValue.h"
#include "lang/scope/Scope.h"
#include "lang/statement/Statement.h"
#include "lang/type/SizeType.h"
#include "lang/utility/Values.h"
#include "validation/Utilities.h"
#include "validation/ValidationLogger.h"

SizeofType::SizeofType(lang::ResolvingHandle<lang::Type> type, lang::Location type_location, lang::Location location)
    : Expression(location)
    , type_(std::move(type))
    , type_location_(type_location)
{}

lang::Type const& SizeofType::targetType() const
{
    return type_;
}

void SizeofType::walkDefinitions()
{
    scope()->addType(type_);
}

void SizeofType::defineType(lang::ResolvingHandle<lang::Type>& type)
{
    type.reroute(scope()->context().getSizeType());
}

bool SizeofType::validate(ValidationLogger& validation_logger) const
{
    if (lang::validation::isTypeUndefined(type_, type_location_, validation_logger)) return false;

    return type_->validate(validation_logger, type_location_);
}

Expression::Expansion SizeofType::expandWith(Expressions, lang::Context& new_context) const
{
    return {Statements(),
            makeOwned<SizeofType>(type_->createUndefinedClone(new_context), type_location_, location()),
            Statements()};
}

void SizeofType::doBuild(CompileContext& context)
{
    llvm::Value* content_value =
        lang::SizeType::buildContentValue(type_->getContentSize(context.llvmModule()), context);
    llvm::Value* native_value = lang::values::contentToNative(type(), content_value, context);

    Shared<lang::WrappedNativeValue> value = makeShared<lang::WrappedNativeValue>(type(), native_value);
    setValue(value);
}
