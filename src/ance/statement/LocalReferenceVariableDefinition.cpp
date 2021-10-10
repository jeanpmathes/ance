#include "LocalReferenceVariableDefinition.h"

#include <utility>

#include "ance/ApplicationVisitor.h"
#include "ance/construct/DefinedFunction.h"
#include "ance/construct/LocalVariable.h"
#include "ance/construct/value/RoughlyCastedValue.h"
#include "ance/expression/Addressof.h"
#include "ance/expression/BindRef.h"
#include "ance/scope/LocalScope.h"
#include "ance/type/PointerType.h"
#include "ance/type/ReferenceType.h"
#include "validation/ValidationLogger.h"

LocalReferenceVariableDefinition* LocalReferenceVariableDefinition::defineReferring(std::string    identifier,
                                                                                    ance::Type*    type,
                                                                                    Expression*    value,
                                                                                    Application&   app,
                                                                                    ance::Location location)
{
    Expression* reference = BindRef::refer(value, app, location);
    return new LocalReferenceVariableDefinition(std::move(identifier), type, reference, location);
}

LocalReferenceVariableDefinition* LocalReferenceVariableDefinition::defineReferringTo(std::string    identifier,
                                                                                      ance::Type*    type,
                                                                                      Expression*    address,
                                                                                      ance::Location location)
{
    Expression* reference = BindRef::referTo(address, location);
    return new LocalReferenceVariableDefinition(std::move(identifier), type, reference, location);
}

LocalReferenceVariableDefinition::LocalReferenceVariableDefinition(std::string    identifier,
                                                                   ance::Type*    type,
                                                                   Expression*    reference,
                                                                   ance::Location location)
    : Statement(location)
    , identifier_(std::move(identifier))
    , type_(type)
    , reference_(reference)
{
    addChild(*reference);
}

void LocalReferenceVariableDefinition::setFunction(ance::DefinedFunction* function)
{
    variable_ =
        function->getFunctionScope()->defineAutoVariable(identifier_,
                                                                 type_,
                                                                 Assigner::REFERENCE_BINDING,
                                                                 reference_->getValue(),
                                                                 location());

    reference_->setContainingScope(function);
}
void LocalReferenceVariableDefinition::validate(ValidationLogger& validation_logger)
{
    if (variable_)
    {
        if (!ance::ReferenceType::isReferenceType(type_))
        {
            validation_logger.logError("Cannot bind reference to variable of non-reference type '" + type_->getName()
                                           + "'",
                                       location());
            return;
        }

        if (!type_->validate(validation_logger, location())) return;

        bool reference_is_valid = reference_->validate(validation_logger);
        if (!reference_is_valid) return;

        ance::Type* reference_type = reference_->type();

        ance::Type* declared_referenced_type = ance::ReferenceType::getReferencedType(type_);
        ance::Type* provided_referenced_type = ance::ReferenceType::getReferencedType(reference_type);

        if (declared_referenced_type != provided_referenced_type)
        {
            validation_logger.logError("Cannot bind '" + declared_referenced_type->getName()
                                           + "' reference to value of type '" + provided_referenced_type->getName()
                                           + "'",
                                       reference_->location());
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
