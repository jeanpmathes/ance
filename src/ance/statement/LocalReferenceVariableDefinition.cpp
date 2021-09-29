#include "LocalReferenceVariableDefinition.h"

#include <utility>

#include "ance/ApplicationVisitor.h"
#include "ance/construct/DefinedFunction.h"
#include "ance/construct/LocalVariable.h"
#include "ance/construct/value/RoughlyCastedValue.h"
#include "ance/expression/Addressof.h"
#include "ance/scope/LocalScope.h"
#include "ance/type/PointerType.h"
#include "ance/type/ReferenceType.h"
#include "validation/ValidationLogger.h"

LocalReferenceVariableDefinition* LocalReferenceVariableDefinition::refer(std::string    identifier,
                                                                          ance::Type*    type,
                                                                          Expression*    value,
                                                                          Application&   app,
                                                                          ance::Location location)
{
    auto* addressof = new Addressof(value, app, location);
    return new LocalReferenceVariableDefinition(std::move(identifier), type, addressof, location);
}

LocalReferenceVariableDefinition* LocalReferenceVariableDefinition::referTo(std::string    identifier,
                                                                            ance::Type*    type,
                                                                            Expression*    address,
                                                                            ance::Location location)
{
    return new LocalReferenceVariableDefinition(std::move(identifier), type, address, location);
}

LocalReferenceVariableDefinition::LocalReferenceVariableDefinition(std::string    identifier,
                                                                   ance::Type*    type,
                                                                   Expression*    address,
                                                                   ance::Location location)
    : Statement(location)
    , identifier_(std::move(identifier))
    , type_(type)
    , address_(address)
{
    addChild(*address);
}

void LocalReferenceVariableDefinition::setFunction(ance::DefinedFunction* function)
{
    variable_ =
        function->getFunctionScope()->defineAutoVariable(identifier_,
                                                         type_,
                                                         Assigner::REFERENCE_BINDING,
                                                         new ance::RoughlyCastedValue(type_, address_->getValue()),
                                                         location());

    address_->setContainingScope(function);
}
void LocalReferenceVariableDefinition::validate(ValidationLogger& validation_logger)
{
    if (variable_)
    {
        bool address_is_valid = address_->validate(validation_logger);
        if (!address_is_valid) return;

        if (!ance::ReferenceType::isReferenceType(type_))
        {
            validation_logger.logError("Cannot bind reference to variable of non-reference type '" + type_->getName()
                                           + "'",
                                       location());
            return;
        }

        ance::Type* address_type = address_->type();

        if (!ance::PointerType::isPointerType(address_type))
        {
            validation_logger.logError("Value of type '" + address_type->getName()
                                           + "' cannot be used as pointer type for reference binding",
                                       address_->location());
            return;
        }

        ance::Type* referenced_type = ance::ReferenceType::getReferencedType(type_);
        ance::Type* pointee_type    = ance::PointerType::getPointeeType(address_type);

        if (referenced_type != pointee_type)
        {
            validation_logger.logError("Cannot bind '" + referenced_type->getName() + "' reference to value of type '"
                                           + pointee_type->getName() + "'",
                                       address_->location());
            return;
        }
    }
    else
    {
        validation_logger.logError("Name '" + identifier_ + "' already defined in the current context", location());
    }
}

void LocalReferenceVariableDefinition::doBuild(CompileContext* context)
{
    variable_->build(context);
}

bool LocalReferenceVariableDefinition::accept(ance::ApplicationVisitor& visitor)
{
    return visitor.visitLocalReferenceVariableDefinition(*this);
}
