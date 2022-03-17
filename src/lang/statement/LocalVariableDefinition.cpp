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

    addChild(*assigned_);
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
    scope->addType(type_);

    variable_ = scope->getLocalScope()->defineLocalVariable(identifier_,
                                                            type_,
                                                            type_location_,
                                                            assigner_,
                                                            assigned_->getValue(),
                                                            location());
    assigned_->setContainingScope(scope);
}

void LocalVariableDefinition::validate(ValidationLogger& validation_logger)
{
    if (variable_)
    {
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
            validation_logger.logError("Cannot declare variable of reference type without binding to a value",
                                       location());
            return;
        }

        lang::Type::checkMismatch(variable->type(), assigned_->type(), assigned_->location(), validation_logger);
    }
    else
    {
        validation_logger.logError("Name '" + identifier_ + "' already defined in the current context", location());
    }
}

void LocalVariableDefinition::doBuild(CompileContext* context)
{
    (*variable_)->buildDefinition(context);
}
