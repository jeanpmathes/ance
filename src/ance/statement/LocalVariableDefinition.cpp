#include "LocalVariableDefinition.h"

#include <utility>

#include "ance/construct/Function.h"
#include "ance/expression/Expression.h"
#include "ance/scope/LocalScope.h"
#include "ance/type/ReferenceType.h"
#include "ance/type/Type.h"
#include "ance/type/VoidType.h"
#include "validation/ValidationLogger.h"

LocalVariableDefinition::LocalVariableDefinition(std::string                       identifier,
                                                 ance::ResolvingHandle<ance::Type> type,
                                                 ance::Location                    type_location,
                                                 Assigner                          assigner,
                                                 std::unique_ptr<Expression>       assigned,
                                                 ance::Location                    location)
    : Statement(location)
    , identifier_(std::move(identifier))
    , type_(type)
    , type_location_(type_location)
    , assigner_(assigner)
    , assigned_(std::move(assigned))
{
    assert(assigner.hasSymbol());
}

void LocalVariableDefinition::setFunction(ance::Function* function)
{
    function->addType(type_);

    variable_ = function->getInsideScope()->defineAutoVariable(identifier_,
                                                               type_,
                                                               type_location_,
                                                               assigner_,
                                                               assigned_->getValue(),
                                                               location());
    assigned_->setContainingScope(function);
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

        ance::Type::checkMismatch(variable->type(), assigned_->type(), assigned_->location(), validation_logger);
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

