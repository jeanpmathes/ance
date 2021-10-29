#include "LocalReferenceVariableDefinition.h"

#include <utility>

#include "ance/construct/Function.h"
#include "ance/construct/Variable.h"
#include "ance/expression/Addressof.h"
#include "ance/expression/BindRef.h"
#include "ance/scope/LocalScope.h"
#include "ance/type/PointerType.h"
#include "ance/type/ReferenceType.h"
#include "validation/ValidationLogger.h"

LocalReferenceVariableDefinition* LocalReferenceVariableDefinition::defineReferring(std::string identifier,
                                                                                    ance::Type* type,
                                                                                    std::unique_ptr<Expression> value,
                                                                                    ance::Location location)
{
    std::unique_ptr<Expression> reference = BindRef::refer(std::move(value), location);
    return new LocalReferenceVariableDefinition(std::move(identifier), type, std::move(reference), location);
}

LocalReferenceVariableDefinition* LocalReferenceVariableDefinition::defineReferringTo(
    std::string                 identifier,
    ance::Type*                 type,
    std::unique_ptr<Expression> address,
    ance::Location              location)
{
    std::unique_ptr<Expression> reference = BindRef::referTo(std::move(address), location);
    return new LocalReferenceVariableDefinition(std::move(identifier), type, std::move(reference), location);
}

LocalReferenceVariableDefinition::LocalReferenceVariableDefinition(std::string                 identifier,
                                                                   ance::Type*                 type,
                                                                   std::unique_ptr<Expression> reference,
                                                                   ance::Location              location)
    : Statement(location)
    , identifier_(std::move(identifier))
    , type_(type)
    , reference_(std::move(reference))
{}

void LocalReferenceVariableDefinition::setFunction(ance::Function* function)
{
    variable_ = function->getInsideScope()->defineAutoVariable(identifier_,
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
    variable_->buildDefinition(context);
}