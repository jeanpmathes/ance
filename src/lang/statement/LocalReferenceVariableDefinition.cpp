#include "LocalReferenceVariableDefinition.h"

#include <memory>
#include <utility>

#include "lang/ApplicationVisitor.h"
#include "lang/Assigner.h"
#include "lang/construct/Function.h"
#include "lang/expression/Addressof.h"
#include "lang/expression/BindRef.h"
#include "validation/Utilities.h"
#include "validation/ValidationLogger.h"

LocalReferenceVariableDefinition::LocalReferenceVariableDefinition(lang::Identifier                  name,
                                                                   lang::ResolvingHandle<lang::Type> type,
                                                                   lang::Location                    type_location,
                                                                   Owned<Expression>                 reference,
                                                                   lang::Location                    location)
    : Statement(location)
    , name_(name)
    , type_(std::move(type))
    , type_location_(type_location)
    , reference_(std::move(reference))
{
    addSubexpression(*reference_);
}

lang::Identifier const& LocalReferenceVariableDefinition::name() const
{
    return name_;
}

lang::Type const& LocalReferenceVariableDefinition::type() const
{
    return type_;
}

Expression const& LocalReferenceVariableDefinition::reference() const
{
    return *reference_;
}

void LocalReferenceVariableDefinition::setScope(lang::Scope& scope)
{
    Statement::setScope(scope);

    scope.asLocalScope()->prepareDefinition(name_);
}

void LocalReferenceVariableDefinition::walkDefinitions()
{
    Statement::walkDefinitions();

    variable_ = scope()->asLocalScope()->defineLocalVariable(name_,
                                                             type_,
                                                             type_location_,
                                                             lang::Assigner::REFERENCE_BINDING,
                                                             reference_->getValue(),
                                                             location());

    scope()->addType(type_);
}

void LocalReferenceVariableDefinition::validate(ValidationLogger& validation_logger) const
{
    assert(variable_.hasValue());

    if (lang::validation::isTypeUndefined(type_, type_location_, validation_logger)) return;

    if (!type_->isReferenceType())
    {
        validation_logger.logError("Cannot bind reference to variable of non-reference type "
                                       + type_->getAnnotatedName(),
                                   type_location_);
        return;
    }

    if (!type_->validate(validation_logger, type_location_)) return;

    bool const reference_is_valid = reference_->validate(validation_logger);
    if (!reference_is_valid) return;

    lang::Type const& reference_type = reference_->type();

    lang::Type const& declared_referenced_type = type_->getElementType();
    lang::Type const& provided_referenced_type = reference_type.getElementType();

    if (!lang::Type::areSame(declared_referenced_type, provided_referenced_type))
    {
        validation_logger.logError("Cannot bind " + declared_referenced_type.getAnnotatedName()
                                       + " reference to value of type " + provided_referenced_type.getAnnotatedName(),
                                   reference_->location());
        return;
    }
}

Statements LocalReferenceVariableDefinition::expandWith(Expressions subexpressions,
                                                        Statements,
                                                        lang::Context& new_context) const
{
    Statements statements;

    statements.emplace_back(makeOwned<LocalReferenceVariableDefinition>(name_,
                                                                        type_->createUndefinedClone(new_context),
                                                                        type_location_,
                                                                        std::move(subexpressions[0]),
                                                                        location()));

    return statements;
}

void LocalReferenceVariableDefinition::doBuild(CompileContext& context)
{
    (*variable_)->buildDefinition(context);
}
