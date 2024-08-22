#include "SizeofType.h"

#include <utility>

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

lang::Entity const& SizeofType::target() const
{
    return *type_;
}

void SizeofType::walkDefinitions()
{
    scope().registerUsage(type_);

    type();
}

void SizeofType::defineType(lang::ResolvingHandle<lang::Type> type)
{
    if (!isInitialized()) return;

    type.reroute(scope().context().getSizeType());
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
