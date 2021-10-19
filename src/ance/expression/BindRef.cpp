#include "BindRef.h"

#include "ance/ApplicationVisitor.h"
#include "ance/construct/value/RoughlyCastedValue.h"
#include "ance/expression/Addressof.h"
#include "ance/type/PointerType.h"
#include "ance/type/ReferenceType.h"
#include "validation/ValidationLogger.h"

std::unique_ptr<BindRef> BindRef::refer(std::unique_ptr<Expression> value, ance::Location location)
{
    auto addressof = std::make_unique<Addressof>(std::move(value), location);
    return std::unique_ptr<BindRef>(new BindRef(std::move(addressof), location));
}

std::unique_ptr<BindRef> BindRef::referTo(std::unique_ptr<Expression> address, ance::Location location)
{
    return std::unique_ptr<BindRef>(new BindRef(std::move(address), location));
}

BindRef::BindRef(std::unique_ptr<Expression> address, ance::Location location)
    : Expression(location)
    , address_(std::move(address))
{
    addChild(*address_);
}

void BindRef::setScope(ance::Scope* scope)
{
    address_->setContainingScope(scope);
}

ance::Type* BindRef::type()
{
    if (!type_)
    {
        ance::Type* element_type = ance::PointerType::getPointeeType(address_->type());
        type_                    = ance::ReferenceType::get(element_type);
    }

    return type_;
}

bool BindRef::validate(ValidationLogger& validation_logger)
{
    bool address_is_valid = address_->validate(validation_logger);
    if (!address_is_valid) return false;

    ance::Type* address_type = address_->type();

    if (!ance::PointerType::isPointerType(address_type))
    {
        validation_logger.logError("Value of type '" + address_type->getName()
                                       + "' cannot be used as pointer type for reference binding",
                                   address_->location());
        return false;
    }

    return true;
}

void BindRef::doBuild(CompileContext*)
{
    setValue(std::make_shared<ance::RoughlyCastedValue>(type(), address_->getValue()));
}

BindRef::~BindRef() = default;

bool BindRef::accept(ance::ApplicationVisitor& visitor)
{
    return visitor.visitBindRef(*this);
}
