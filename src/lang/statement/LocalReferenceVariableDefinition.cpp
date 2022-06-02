#include "LocalReferenceVariableDefinition.h"

#include <memory>
#include <utility>

#include "lang/construct/Function.h"
#include "lang/expression/Addressof.h"
#include "lang/expression/BindRef.h"
#include "lang/scope/LocalScope.h"
#include "validation/ValidationLogger.h"
#include "lang/Assigner.h"

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
    addSubexpression(*reference_);
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
    Statement::setScope(scope);

    scope->asLocalScope()->prepareDefinition(identifier_);
}

void LocalReferenceVariableDefinition::walkDefinitions()
{
    Statement::walkDefinitions();

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
    assert(variable_);

    if (!type_->isDefined())
    {
        validation_logger.logError("Cannot bind reference to variable of undefined type " + type_->getAnnotatedName(),
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
                                       + " reference to value of type " + provided_referenced_type->getAnnotatedName(),
                                   reference_->location());
        return;
    }
}

Statements LocalReferenceVariableDefinition::expandWith(Expressions subexpressions, Statements) const
{
    Statements statements;

    statements.push_back(std::make_unique<LocalReferenceVariableDefinition>(identifier_,
                                                                            type_->toUndefined(),
                                                                            type_location_,
                                                                            std::move(subexpressions[0]),
                                                                            location()));

    return statements;
}

void LocalReferenceVariableDefinition::doBuild(CompileContext* context)
{
    (*variable_)->buildDefinition(context);
}
