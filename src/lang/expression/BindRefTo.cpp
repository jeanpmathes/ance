#include "BindRefTo.h"

#include <memory>

#include "lang/construct/value/RoughlyCastedValue.h"
#include "lang/statement/Statement.h"
#include "lang/type/PointerType.h"
#include "lang/type/ReferenceType.h"
#include "validation/ValidationLogger.h"

BindRefTo::BindRefTo(std::unique_ptr<Expression> address, lang::Location location)
    : Expression(location)
    , address_(std::move(address))
{
    addSubexpression(*address_);
}

Expression& BindRefTo::address() const
{
    return *address_;
}

lang::ResolvingHandle<lang::Type> BindRefTo::type() const
{
    if (!type_)
    {
        lang::ResolvingHandle<lang::Type> element_type = address_->type()->getElementType();
        type_                                          = lang::ReferenceType::get(element_type);
    }

    return *type_;
}

bool BindRefTo::validate(ValidationLogger& validation_logger) const
{
    bool address_is_valid = address_->validate(validation_logger);
    if (!address_is_valid) return false;

    lang::ResolvingHandle<lang::Type> address_type = address_->type();

    if (!address_type->isPointerType())
    {
        validation_logger.logError("Value of type " + address_type->getAnnotatedName()
                                       + " cannot be used as pointer type for reference binding",
                                   address_->location());
        return false;
    }

    return true;
}

Expression::Expansion BindRefTo::expandWith(Expressions subexpressions) const
{
    return {Statements(), std::make_unique<BindRefTo>(std::move(subexpressions[0]), location()), Statements()};
}

void BindRefTo::doBuild(CompileContext*)
{
    setValue(std::make_shared<lang::RoughlyCastedValue>(type(), address_->getValue()));
}

BindRefTo::~BindRefTo() = default;
