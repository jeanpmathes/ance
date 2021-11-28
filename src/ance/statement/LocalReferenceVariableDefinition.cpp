#include "LocalReferenceVariableDefinition.h"

#include <utility>

#include "ance/construct/Function.h"
#include "ance/expression/Addressof.h"
#include "ance/expression/BindRef.h"
#include "ance/scope/LocalScope.h"
#include "ance/type/PointerType.h"
#include "ance/type/ReferenceType.h"
#include "validation/ValidationLogger.h"

LocalReferenceVariableDefinition* LocalReferenceVariableDefinition::defineReferring(
    std::string                       identifier,
    ance::ResolvingHandle<ance::Type> type,
    ance::Location                    type_location,
    std::unique_ptr<Expression>       value,
    ance::Location                    location)
{
    std::unique_ptr<Expression> reference = BindRef::refer(std::move(value), location);
    return new LocalReferenceVariableDefinition(std::move(identifier),
                                                type,
                                                type_location,
                                                std::move(reference),
                                                location);
}

LocalReferenceVariableDefinition* LocalReferenceVariableDefinition::defineReferringTo(
    std::string                       identifier,
    ance::ResolvingHandle<ance::Type> type,
    ance::Location                    type_location,
    std::unique_ptr<Expression>       address,
    ance::Location                    location)
{
    std::unique_ptr<Expression> reference = BindRef::referTo(std::move(address), location);
    return new LocalReferenceVariableDefinition(std::move(identifier),
                                                type,
                                                type_location,
                                                std::move(reference),
                                                location);
}

LocalReferenceVariableDefinition::LocalReferenceVariableDefinition(std::string                       identifier,
                                                                   ance::ResolvingHandle<ance::Type> type,
                                                                   ance::Location                    type_location,
                                                                   std::unique_ptr<Expression>       reference,
                                                                   ance::Location                    location)
    : Statement(location)
    , identifier_(std::move(identifier))
    , type_(type)
    , type_location_(type_location)
    , reference_(std::move(reference))
{}

void LocalReferenceVariableDefinition::setFunction(ance::Function* function)
{
    function->addType(type_);

    variable_ = function->getInsideScope()->defineAutoVariable(identifier_,
                                                               type_,
                                                               type_location_,
                                                               Assigner::REFERENCE_BINDING,
                                                               reference_->getValue(),
                                                               location());

    reference_->setContainingScope(function);
}
void LocalReferenceVariableDefinition::validate(ValidationLogger& validation_logger)
{
    if (variable_)
    {
        if (!type_->isDefined())
        {
            validation_logger.logError("Cannot bind reference to variable of undefined type '" + type_->getName() + "'",
                                       type_location_);
            return;
        }

        if (!ance::ReferenceType::isReferenceType(type_))
        {
            validation_logger.logError("Cannot bind reference to variable of non-reference type '" + type_->getName()
                                           + "'",
                                       type_location_);
            return;
        }

        if (!type_->validate(validation_logger, type_location_)) return;

        bool reference_is_valid = reference_->validate(validation_logger);
        if (!reference_is_valid) return;

        ance::ResolvingHandle<ance::Type> reference_type = reference_->type();

        ance::ResolvingHandle<ance::Type> declared_referenced_type = ance::ReferenceType::getReferencedType(type_);
        ance::ResolvingHandle<ance::Type> provided_referenced_type =
            ance::ReferenceType::getReferencedType(reference_type);

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
    (*variable_)->buildDefinition(context);
}