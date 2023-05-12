#include "LocalVariableDefinition.h"

#include <utility>

#include "lang/ApplicationVisitor.h"
#include "lang/Assigner.h"
#include "lang/construct/Function.h"
#include "lang/expression/Expression.h"
#include "lang/type/Type.h"
#include "validation/Utilities.h"
#include "validation/ValidationLogger.h"

LocalVariableDefinition::LocalVariableDefinition(lang::Identifier                            name,
                                                 Optional<lang::ResolvingHandle<lang::Type>> type,
                                                 lang::Location                              type_location,
                                                 lang::Assigner                              assigner,
                                                 Optional<Owned<Expression>>                 assigned,
                                                 lang::Location                              location)
    : Statement(location)
    , name_(name)
    , type_opt_(type)
    , type_(lang::Type::getUndefined())
    , type_location_(type_location)
    , assigner_(assigner)
    , assigned_(std::move(assigned))
{
    if (assigned_.hasValue()) { addSubexpression(*assigned_.value()); }

    if (type_opt_.hasValue()) { type_.reroute(type_opt_.value()); }
    else if (assigned_.hasValue()) { type_.reroute(assigned_.value()->type()); }
}

lang::Identifier const& LocalVariableDefinition::name() const
{
    return name_;
}

lang::Type const* LocalVariableDefinition::type() const
{
    if (type_opt_.hasValue())
    {
        lang::Type const& type = type_opt_.value();
        return &type;
    }

    return nullptr;
}

lang::Assigner LocalVariableDefinition::assigner() const
{
    return assigner_;
}

Expression const* LocalVariableDefinition::assigned() const
{
    return getPtr(assigned_);
}

void LocalVariableDefinition::setScope(lang::Scope& scope)
{
    Statement::setScope(scope);

    scope.asLocalScope()->prepareDefinition(name_);
}

void LocalVariableDefinition::walkDefinitions()
{
    Statement::walkDefinitions();

    Optional<Shared<lang::Value>> assigned_value;
    if (assigned_.hasValue()) { assigned_value = assigned_.value()->getValue(); }

    variable_ = scope()->asLocalScope()->defineLocalVariable(name_,
                                                             type_,
                                                             type_location_,
                                                             assigner_,
                                                             assigned_value,
                                                             location());

    if (type_opt_.hasValue()) scope()->addType(type_opt_.value());
}

void LocalVariableDefinition::postResolve()
{
    Statement::postResolve();
}

void LocalVariableDefinition::validate(ValidationLogger& validation_logger) const
{
    assert(variable_.hasValue());
    auto const& variable = *variable_;

    auto tn = type_->name();
    (void) tn;

    assert(variable->type() == type_);

    if (assigned_.hasValue())
    {
        if (!assigned_.value()->validate(validation_logger)) return;
    }

    if (not type_opt_.hasValue() && !assigned_.hasValue())
    {
        validation_logger.logError("Default-initialized local variable must have explicit type", location());
        return;
    }

    if (lang::validation::isTypeUndefined(type_, scope(), type_location_, validation_logger)) return;

    if (!type_->validate(validation_logger, type_location_)) return;

    if (type_->isVoidType())
    {
        validation_logger.logError("Local variable cannot have 'void' type", type_location_);
        return;
    }

    if (type_->isReferenceType())
    {
        validation_logger.logError("Cannot declare variable of reference type without binding to a value", location());
        return;
    }

    if (assigned_.hasValue())
    {
        if (!assigned_.value()->type().isDefined()) return;

        lang::Type::checkMismatch(variable->type(),
                                  assigned_.value()->type(),
                                  assigned_.value()->location(),
                                  validation_logger);
    }
}

Statements LocalVariableDefinition::expandWith(Expressions subexpressions, Statements, lang::Context& new_context) const
{
    Statements statements;

    Optional<lang::ResolvingHandle<lang::Type>> type;
    if (type_opt_.hasValue()) type = type_opt_.value()->createUndefinedClone(new_context);

    Optional<Owned<Expression>> assigned;
    if (subexpressions.size() == 1) assigned = std::move(subexpressions[0]);

    statements.emplace_back(
        makeOwned<LocalVariableDefinition>(name_, type, type_location_, assigner_, std::move(assigned), location()));

    return statements;
}

void LocalVariableDefinition::doBuild(CompileContext& context)
{
    (*variable_)->buildDefinition(context);
}
