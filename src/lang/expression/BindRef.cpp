#include "BindRef.h"

#include "lang/construct/value/RoughlyCastedValue.h"
#include "lang/expression/Addressof.h"
#include "lang/type/PointerType.h"
#include "lang/type/ReferenceType.h"
#include "validation/ValidationLogger.h"

std::unique_ptr<BindRef> BindRef::refer(std::unique_ptr<Expression> value, lang::Location location)
{
    auto addressof = std::make_unique<Addressof>(std::move(value), location);
    return std::unique_ptr<BindRef>(new BindRef(std::move(addressof), location));
}

std::unique_ptr<BindRef> BindRef::referTo(std::unique_ptr<Expression> address, lang::Location location)
{
    return std::unique_ptr<BindRef>(new BindRef(std::move(address), location));
}

BindRef::BindRef(std::unique_ptr<Expression> address, lang::Location location)
    : Expression(location)
    , address_(std::move(address))
{
    addSubexpression(*address_);
}

Expression& BindRef::address() const
{
    return *address_;
}

lang::ResolvingHandle<lang::Type> BindRef::type()
{
    if (!type_)
    {
        lang::ResolvingHandle<lang::Type> element_type = address_->type()->getElementType();
        type_                                          = lang::ReferenceType::get(element_type);
    }

    return *type_;
}

bool BindRef::validate(ValidationLogger& validation_logger)
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

void BindRef::doBuild(CompileContext*)
{
    setValue(std::make_shared<lang::RoughlyCastedValue>(type(), address_->getValue()));
}

BindRef::~BindRef() = default;
