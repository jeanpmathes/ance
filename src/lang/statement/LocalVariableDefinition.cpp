#include "LocalVariableDefinition.h"

#include <utility>

#include "lang/construct/Function.h"
#include "lang/expression/Expression.h"
#include "lang/scope/LocalScope.h"
#include "lang/type/Type.h"
#include "validation/ValidationLogger.h"
#include "lang/Assigner.h"
#include "lang/expression/DefaultValue.h"

LocalVariableDefinition::LocalVariableDefinition(std::string                       identifier,
                                                 lang::ResolvingHandle<lang::Type> type,
                                                 lang::Location                    type_location,
                                                 lang::Assigner                    assigner,
                                                 std::unique_ptr<Expression>       assigned,
                                                 lang::Location                    location)
    : Statement(location)
    , identifier_(std::move(identifier))
    , type_(type)
    , type_location_(type_location)
    , assigner_(assigner)
    , assigned_ptr_(assigned.get())
    , assigned_(assigned ? std::move(assigned) : std::make_unique<DefaultValue>(type, location))
{
    assert(assigner.hasSymbol());

    addSubexpression(*assigned_);
}

const std::string& LocalVariableDefinition::identifier() const
{
    return identifier_;
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
    return assigned_ptr_;
}

void LocalVariableDefinition::setScope(lang::Scope* scope)
{
    Statement::setScope(scope);

    scope->asLocalScope()->prepareDefinition(identifier_);
}

void LocalVariableDefinition::walkDefinitions()
{
    Statement::walkDefinitions();

    variable_ = scope()->asLocalScope()->defineLocalVariable(identifier_,
                                                             type_,
                                                             type_location_,
                                                             assigner_,
                                                             assigned_->getValue(),
                                                             location());

    scope()->addType(type_);
}

void LocalVariableDefinition::validate(ValidationLogger& validation_logger)
{
    assert(variable_);
    auto variable = *variable_;

    bool assigned_is_valid = assigned_->validate(validation_logger);
    if (!assigned_is_valid) return;

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

    lang::Type::checkMismatch(variable->type(), assigned_->type(), assigned_->location(), validation_logger);
}

Statements LocalVariableDefinition::expandWith(Expressions subexpressions, Statements) const
{
    Statements statements;

    statements.push_back(std::make_unique<LocalVariableDefinition>(identifier_,
                                                  type_->toUndefined(),
                                                  type_location_,
                                                  assigner_,
                                                  assigned_ptr_ ? std::move(subexpressions[0]) : nullptr,
                                                  location()));

    return statements;
}

void LocalVariableDefinition::doBuild(CompileContext* context)
{
    (*variable_)->buildDefinition(context);
}
