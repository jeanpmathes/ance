#include "SizeofType.h"

#include <utility>

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/scope/Scope.h"
#include "lang/statement/Statement.h"
#include "lang/type/SizeType.h"
#include "validation/Utilities.h"
#include "validation/ValidationLogger.h"

SizeofType::SizeofType(lang::ResolvingHandle<lang::Type> type, lang::Location type_location, lang::Location location)
    : Expression(location)
    , type_(std::move(type))
    , type_location_(type_location)
{}

lang::Type const& SizeofType::targetType() const
{
    return *type_.as<lang::Type>();
}

void SizeofType::walkDefinitions()
{
    scope()->registerUsage(type_);
}

void SizeofType::defineType(lang::ResolvingHandle<lang::Type> type)
{
    if (scope() == nullptr) return;

    type.reroute(scope()->context().getSizeType());
}

bool SizeofType::validate(ValidationLogger& validation_logger) const
{
    if (lang::Type::checkMismatch<lang::Type>(type_, "type", type_location_, validation_logger)) return false;

    return type_.as<lang::Type>()->validate(validation_logger, type_location_);
}

Expression::Expansion SizeofType::expandWith(Expressions, lang::Context& new_context) const
{
    return {Statements(),
            makeOwned<SizeofType>(type_->getUndefinedClone<lang::Type>(new_context), type_location_, location()),
            Statements()};
}

void SizeofType::doBuild(CompileContext& context)
{
    auto actual_type = lang::Type::makeMatching<lang::Type>(type_);
    setValue(context.exec().getSizeOf(actual_type));
}
