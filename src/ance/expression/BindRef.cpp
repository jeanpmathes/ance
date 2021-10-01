#include "BindRef.h"

#include "ance/ApplicationVisitor.h"
#include "ance/construct/value/RoughlyCastedValue.h"
#include "ance/expression/Addressof.h"
#include "ance/type/PointerType.h"
#include "ance/type/ReferenceType.h"
#include "validation/ValidationLogger.h"

BindRef* BindRef::refer(Expression* value, Application& app, ance::Location location)
{
    auto* addressof = new Addressof(value, app, location);
    return new BindRef(addressof, app, location);
}

BindRef* BindRef::referTo(Expression* address, Application& app, ance::Location location)
{
    return new BindRef(address, app, location);
}

BindRef::BindRef(Expression* address, Application& application, ance::Location location)
    : Expression(location)
    , address_(address)
    , application_(application)
{
    addChild(*address);
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
        type_                    = ance::ReferenceType::get(application_, element_type);
    }

    return type_;
}

bool BindRef::validate(ValidationLogger& validation_logger)
{
    bool address_is_valid = address_->validate(validation_logger);
    if (!address_is_valid) return false;

    if (!type()->validate(validation_logger, location())) return false;

    ance::Type* address_type = address_->type();

    if (!ance::PointerType::isPointerType(address_type))
    {
        validation_logger.logError("Value of type '" + address_type->getName()
                                       + "' cannot be used as pointer type for reference binding",
                                   address_->location());
        return false;
    }

    ance::Type* referenced_type = ance::ReferenceType::getReferencedType(type_);
    ance::Type* pointee_type    = ance::PointerType::getPointeeType(address_type);

    if (referenced_type != pointee_type)
    {
        validation_logger.logError("Cannot bind '" + referenced_type->getName() + "' reference to value of type '"
                                       + pointee_type->getName() + "'",
                                   address_->location());
        return false;
    }

    return true;
}

void BindRef::doBuild(CompileContext*)
{
    setValue(new ance::RoughlyCastedValue(type(), address_->getValue()));
}

BindRef::~BindRef() = default;

bool BindRef::accept(ance::ApplicationVisitor& visitor)
{
    return visitor.visitBindRef(*this);
}
