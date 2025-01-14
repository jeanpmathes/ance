#include "LocalReferenceVariableDefinition.h"

#include <memory>
#include <utility>

#include "lang/ApplicationVisitor.h"
#include "lang/Assigner.h"
#include "lang/construct/Function.h"
#include "lang/expression/Addressof.h"
#include "lang/expression/BindRef.h"
#include "lang/type/TypeDefinition.h"
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
    return *type_.as<lang::Type>();
}

Expression const& LocalReferenceVariableDefinition::reference() const
{
    return *reference_;
}

lang::Variable const& LocalReferenceVariableDefinition::variable() const
{
    assert(variable_.hasValue());
    return *variable_;
}

void LocalReferenceVariableDefinition::setScope(lang::Scope& scope)
{
    Statement::setScope(scope);

    scope.asOrderedScope()->prepareDefinition(name_);
}

void LocalReferenceVariableDefinition::walkDefinitions()
{
    Statement::walkDefinitions();

    if (type_.is<lang::Type>())
    {
        lang::OwningHandle<lang::Variable> variable =
            lang::LocalVariable::makeLocalVariable(name_,
                                                   type_.as<lang::Type>().value(),
                                                   type_location_,
                                                   lang::Assigner::REFERENCE_BINDING,
                                                   reference_.get(),
                                                   scope(),
                                                   location());
        variable_ = variable.handle();

        scope().addEntity(std::move(variable));
        scope().registerUsage(type_);
    }
}

bool LocalReferenceVariableDefinition::validate(ValidationLogger& validation_logger) const
{
    if (lang::Type::checkMismatch<lang::Type>(type_, "type", type_location_, validation_logger)) return false;

    assert(variable_.hasValue());
    auto type = type_.as<lang::Type>();

    if (!type->isReferenceType())
    {
        validation_logger.logError("Cannot bind reference to variable of non-reference type "
                                       + type->getAnnotatedName(),
                                   type_location_);
        return false;
    }

    if (!type->validate(validation_logger, type_location_)) return false;

    bool const reference_is_valid = reference_->validate(validation_logger);
    if (!reference_is_valid) return false;

    lang::Type const& reference_type = reference_->type();

    lang::Type const& declared_referenced_type = type->getElementType();
    lang::Type const& provided_referenced_type = reference_type.getElementType();

    if (!lang::Type::areSame(declared_referenced_type, provided_referenced_type))
    {
        validation_logger.logError("Cannot bind " + declared_referenced_type.getAnnotatedName()
                                       + " reference to value of type " + provided_referenced_type.getAnnotatedName(),
                                   reference_->location());
        return false;
    }

    return true;
}

Statements LocalReferenceVariableDefinition::expandWith(Expressions subexpressions,
                                                        Statements,
                                                        lang::Context& new_context) const
{
    Statements statements;

    statements.emplace_back(
        makeOwned<LocalReferenceVariableDefinition>(name_,
                                                    type_->getUndefinedClone<lang::Type>(new_context),
                                                    type_location_,
                                                    std::move(subexpressions[0]),
                                                    location()));

    return statements;
}
