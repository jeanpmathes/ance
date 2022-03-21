#include "LocalReferenceVariableDefinition.h"

#include <utility>

#include "lang/construct/Function.h"
#include "lang/expression/Addressof.h"
#include "lang/expression/BindRef.h"
#include "lang/scope/LocalScope.h"
#include "validation/ValidationLogger.h"
#include "lang/Assigner.h"

std::unique_ptr<LocalReferenceVariableDefinition> LocalReferenceVariableDefinition::defineReferring(
    std::string                       identifier,
    lang::ResolvingHandle<lang::Type> type,
    lang::Location                    type_location,
    std::unique_ptr<Expression>       value,
    lang::Location                    location)
{
    std::unique_ptr<Expression> reference = BindRef::refer(std::move(value), location);
    auto*                       def       = new LocalReferenceVariableDefinition(std::move(identifier),
                                                     type,
                                                     type_location,
                                                     std::move(reference),
                                                     location);
    return std::unique_ptr<LocalReferenceVariableDefinition>(def);
}

std::unique_ptr<LocalReferenceVariableDefinition> LocalReferenceVariableDefinition::defineReferringTo(
    std::string                       identifier,
    lang::ResolvingHandle<lang::Type> type,
    lang::Location                    type_location,
    std::unique_ptr<Expression>       address,
    lang::Location                    location)
{
    std::unique_ptr<Expression> reference = BindRef::referTo(std::move(address), location);
    auto*                       def       = new LocalReferenceVariableDefinition(std::move(identifier),
                                                     type,
                                                     type_location,
                                                     std::move(reference),
                                                     location);
    return std::unique_ptr<LocalReferenceVariableDefinition>(def);
}

LocalReferenceVariableDefinition::LocalReferenceVariableDefinition(std::string                       identifier,
                                                                   lang::ResolvingHandle<lang::Type> type,
                                                                   lang::Location                    type_location,
                                                                   std::unique_ptr<Expression>       reference,
                                                                   lang::Location                    location)
    : Statement(location)
    , identifier_(std::move(identifier))
    , type_(type)
    , type_location_(type_location)
    , reference_(std::move(reference))
{
    addChild(*reference_);
}

const std::string& LocalReferenceVariableDefinition::identifier() const
{
    return identifier_;
}

lang::ResolvingHandle<lang::Type> LocalReferenceVariableDefinition::type() const
{
    return type_;
}

Expression& LocalReferenceVariableDefinition::reference() const
{
    return *reference_;
}

void LocalReferenceVariableDefinition::setScope(lang::Scope* scope)
{
    reference_->setContainingScope(scope);
}

void LocalReferenceVariableDefinition::walkDefinitions()
{
    reference_->walkDefinitions();

    variable_ = scope()->asLocalScope()->defineLocalVariable(identifier_,
                                                             type_,
                                                             type_location_,
                                                             lang::Assigner::REFERENCE_BINDING,
                                                             reference_->getValue(),
                                                             location());

    scope()->addType(type_);
}

void LocalReferenceVariableDefinition::validate(ValidationLogger& validation_logger)
{
    if (variable_)
    {
        if (!type_->isDefined())
        {
            validation_logger.logError("Cannot bind reference to variable of undefined type "
                                           + type_->getAnnotatedName(),
                                       type_location_);
            return;
        }

        if (!type_->isReferenceType())
        {
            validation_logger.logError("Cannot bind reference to variable of non-reference type "
                                           + type_->getAnnotatedName(),
                                       type_location_);
            return;
        }

        if (!type_->validate(validation_logger, type_location_)) return;

        bool reference_is_valid = reference_->validate(validation_logger);
        if (!reference_is_valid) return;

        lang::ResolvingHandle<lang::Type> reference_type = reference_->type();

        lang::ResolvingHandle<lang::Type> declared_referenced_type = type_->getElementType();
        lang::ResolvingHandle<lang::Type> provided_referenced_type = reference_type->getElementType();

        if (!lang::Type::areSame(declared_referenced_type, provided_referenced_type))
        {
            validation_logger.logError("Cannot bind " + declared_referenced_type->getAnnotatedName()
                                           + " reference to value of type "
                                           + provided_referenced_type->getAnnotatedName(),
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
