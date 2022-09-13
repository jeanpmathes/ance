#include "LocalVariableDefinition.h"

#include <utility>

#include "lang/ApplicationVisitor.h"
#include "lang/Assigner.h"
#include "lang/construct/Function.h"
#include "lang/expression/Expression.h"
#include "lang/type/Type.h"
#include "validation/ValidationLogger.h"

LocalVariableDefinition::LocalVariableDefinition(lang::Identifier                                 name,
                                                 std::optional<lang::ResolvingHandle<lang::Type>> type,
                                                 lang::Location                                   type_location,
                                                 lang::Assigner                                   assigner,
                                                 std::unique_ptr<Expression>                      assigned,
                                                 lang::Location                                   location)
    : Statement(location)
    , name_(std::move(name))
    , type_opt_(std::move(type))
    , type_(lang::Type::getUndefined())
    , type_location_(type_location)
    , assigner_(assigner)
    , assigned_(std::move(assigned))
{
    if (assigned_) { addSubexpression(*assigned_); }

    if (type_opt_) { type_ = type_opt_.value(); }
}

const lang::Identifier& LocalVariableDefinition::name() const
{
    return name_;
}

std::optional<lang::ResolvingHandle<lang::Type>> LocalVariableDefinition::type() const
{
    return type_opt_;
}

lang::Assigner LocalVariableDefinition::assigner() const
{
    return assigner_;
}

Expression* LocalVariableDefinition::assigned() const
{
    return assigned_.get();
}

void LocalVariableDefinition::setScope(lang::Scope& scope)
{
    Statement::setScope(scope);

    scope.asLocalScope()->prepareDefinition(name_);
}

void LocalVariableDefinition::walkDefinitions()
{
    Statement::walkDefinitions();

    rerouteIfNeeded();

    variable_ = scope()->asLocalScope()->defineLocalVariable(name_,
                                                             type_,
                                                             type_location_,
                                                             assigner_,
                                                             assigned_ ? assigned_->getValue() : nullptr,
                                                             location());

    if (type_opt_) scope()->addType(type_opt_.value());
}

void LocalVariableDefinition::postResolve()
{
    Statement::postResolve();

    rerouteIfNeeded();
}

void LocalVariableDefinition::validate(ValidationLogger& validation_logger) const
{
    assert(variable_);
    auto variable = *variable_;

    assert(variable->type() == type_);

    if (assigned_)
    {
        if (!assigned_->validate(validation_logger)) return;
    }

    if (not type_opt_.has_value() && assigned_ == nullptr)
    {
        validation_logger.logError("Default-initialized local variable must have an explicit type", location());
        return;
    }

    if (!type_->isDefined())
    {
        validation_logger.logError("Type " + variable->type()->getAnnotatedName() + " not defined", type_location_);

        return;
    }

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

    if (assigned_)
    {
        lang::Type::checkMismatch(variable->type(), assigned_->type(), assigned_->location(), validation_logger);
    }
}

Statements LocalVariableDefinition::expandWith(Expressions subexpressions, Statements) const
{
    Statements statements;

    std::optional<lang::ResolvingHandle<lang::Type>> type;
    if (type_opt_) type = type_opt_.value()->toUndefined();

    statements.push_back(
        std::make_unique<LocalVariableDefinition>(name_,
                                                  type,
                                                  type_location_,
                                                  assigner_,
                                                  subexpressions.size() == 1 ? std::move(subexpressions[0]) : nullptr,
                                                  location()));

    return statements;
}

void LocalVariableDefinition::doBuild(CompileContext& context)
{
    (*variable_)->buildDefinition(context);
}

void LocalVariableDefinition::rerouteIfNeeded()
{
    if (assigned_ && not type_opt_.has_value())
    {
        auto assigned_type = assigned_->tryGetType();
        if (assigned_type && assigned_type.value() != type_) { type_.reroute(assigned_type.value()); }
    }
}

