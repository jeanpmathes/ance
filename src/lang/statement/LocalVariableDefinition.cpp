#include "LocalVariableDefinition.h"

#include <utility>

#include "lang/construct/Function.h"
#include "lang/expression/Expression.h"
#include "lang/type/Type.h"
#include "validation/ValidationLogger.h"
#include "lang/Assigner.h"

LocalVariableDefinition::LocalVariableDefinition(lang::Identifier                  name,
                                                 lang::ResolvingHandle<lang::Type> type,
                                                 lang::Location                    type_location,
                                                 lang::Assigner                    assigner,
                                                 std::unique_ptr<Expression>       assigned,
                                                 lang::Location                    location)
    : Statement(location)
    , name_(std::move(name))
    , type_(type)
    , type_location_(type_location)
    , assigner_(assigner)
    , assigned_(std::move(assigned))
{
    if (assigned_) { addSubexpression(*assigned_); }
}

const lang::Identifier& LocalVariableDefinition::name() const
{
    return name_;
}

lang::ResolvingHandle<lang::Type> LocalVariableDefinition::type() const
{
    return type_;
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

    variable_ = scope()->asLocalScope()->defineLocalVariable(name_,
                                                             type_,
                                                             type_location_,
                                                             assigner_,
                                                             assigned_ ? assigned_->getValue() : nullptr,
                                                             location());

    scope()->addType(type_);
}

void LocalVariableDefinition::validate(ValidationLogger& validation_logger) const
{
    assert(variable_);
    auto variable = *variable_;

    if (!variable->type()->isDefined())
    {
        validation_logger.logError("Type " + variable->type()->getAnnotatedName() + " not defined", type_location_);

        return;
    }

    if (!variable->type()->validate(validation_logger, type_location_)) return;

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
        if (!assigned_->validate(validation_logger)) return;

        lang::Type::checkMismatch(variable->type(), assigned_->type(), assigned_->location(), validation_logger);
    }
}

Statements LocalVariableDefinition::expandWith(Expressions subexpressions, Statements) const
{
    Statements statements;

    statements.push_back(
        std::make_unique<LocalVariableDefinition>(name_,
                                                  type_->toUndefined(),
                                                  type_location_,
                                                  assigner_,
                                                  subexpressions.size() == 1 ? std::move(subexpressions[0]) : nullptr,
                                                  location()));

    return statements;
}

void LocalVariableDefinition::doBuild(CompileContext* context)
{
    (*variable_)->buildDefinition(context);
}
