#include "BindRefTo.h"

#include <memory>

#include "lang/ApplicationVisitor.h"
#include "lang/construct/value/RoughlyCastedValue.h"
#include "lang/statement/Statement.h"
#include "validation/ValidationLogger.h"

BindRefTo::BindRefTo(Owned<Expression> address, lang::Location location)
    : Expression(location)
    , address_(std::move(address))
{
    addSubexpression(*address_);
}

Expression const& BindRefTo::address() const
{
    return *address_;
}

void BindRefTo::defineType(lang::ResolvingHandle<lang::Type> type)
{
    if (scope() == nullptr) return;

    auto argument_type = address_->type();

    if (argument_type->isDefined() && (argument_type->isPointerType() || argument_type->isBufferType()))
    {
        auto element_type = argument_type->getElementType();
        type.reroute(scope()->context().getReferenceType(element_type));
    }
}

bool BindRefTo::validate(ValidationLogger& validation_logger) const
{
    bool const address_is_valid = address_->validate(validation_logger);
    if (!address_is_valid) return false;

    lang::Type const& address_type = address_->type();

    if (!address_type.isPointerType() && !address_type.isBufferType())
    {
        validation_logger.logError("Value of type " + address_type.getAnnotatedName()
                                       + " cannot be used as pointer or buffer type for reference binding",
                                   address_->location());
        return false;
    }

    return true;
}

Expression::Expansion BindRefTo::expandWith(Expressions subexpressions, lang::Context&) const
{
    return {Statements(), makeOwned<BindRefTo>(std::move(subexpressions[0]), location()), Statements()};
}

void BindRefTo::doBuild(CompileContext& context)
{
    setValue(makeShared<lang::RoughlyCastedValue>(type(), address_->getValue(), context));
}

BindRefTo::~BindRefTo() = default;
