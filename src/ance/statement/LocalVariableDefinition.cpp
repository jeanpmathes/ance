#include "LocalVariableDefinition.h"

#include <utility>

#include "ance/construct/Function.h"
#include "ance/construct/Variable.h"
#include "ance/expression/Expression.h"
#include "ance/scope/LocalScope.h"
#include "ance/type/ReferenceType.h"
#include "ance/type/VoidType.h"
#include "validation/ValidationLogger.h"

LocalVariableDefinition::LocalVariableDefinition(std::string                 identifier,
                                                 ance::Type*                 type,
                                                 Assigner                    assigner,
                                                 std::unique_ptr<Expression> assigned,
                                                 ance::Location              location)
    : Statement(location)
    , identifier_(std::move(identifier))
    , type_(type)
    , assigner_(assigner)
    , assigned_(std::move(assigned))
{
    assert(assigner != Assigner::REFERENCE_BINDING);
}

void LocalVariableDefinition::setFunction(ance::Function* function)
{
    variable_ = function->getInsideScope()->defineAutoVariable(identifier_,
                                                               type_,
                                                               assigner_,
                                                               assigned_->getValue(),
                                                               location());
    assigned_->setContainingScope(function);
}

void LocalVariableDefinition::validate(ValidationLogger& validation_logger)
{
    if (variable_)
    {
        bool assigned_is_valid = assigned_->validate(validation_logger);
        if (!assigned_is_valid) return;

        if (!variable_->type()->validate(validation_logger, location())) return;

        if (type_ == ance::VoidType::get())
        {
            validation_logger.logError("Local variable cannot have 'void' type", location());
            return;
        }

        if (ance::ReferenceType::isReferenceType(type_))
        {
            validation_logger.logError("Cannot declare variable of reference type without binding to a value",
                                       location());
            return;
        }

        ance::Type::checkMismatch(variable_->type(), assigned_->type(), assigned_->location(), validation_logger);
    }
    else
    {
        validation_logger.logError("Name '" + identifier_ + "' already defined in the current context", location());
    }
}

void LocalVariableDefinition::doBuild(CompileContext* context)
{
    variable_->buildDefinition(context);
}

