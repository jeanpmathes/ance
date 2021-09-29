#include "LocalVariableDefinition.h"

#include <utility>

#include "ance/ApplicationVisitor.h"
#include "ance/construct/DefinedFunction.h"
#include "ance/construct/LocalVariable.h"
#include "ance/expression/Expression.h"
#include "ance/scope/LocalScope.h"
#include "ance/type/Type.h"
#include "validation/ValidationLogger.h"

LocalVariableDefinition::LocalVariableDefinition(std::string    identifier,
                                                 ance::Type*    type,
                                                 Assigner       assigner,
                                                 Expression*    assigned,
                                                 ance::Location location)
    : Statement(location)
    , identifier_(std::move(identifier))
    , type_(type)
    , assigner_(assigner)
    , assigned_(assigned)
{
    assert(assigner != Assigner::REFERENCE_BINDING);

    addChild(*assigned);
}

void LocalVariableDefinition::setFunction(ance::DefinedFunction* function)
{
    variable_ = function->getFunctionScope()->defineAutoVariable(identifier_,
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

        ance::Type::checkMismatch(variable_->type(), assigned_->type(), assigned_->location(), validation_logger);
    }
    else
    {
        validation_logger.logError("Name '" + identifier_ + "' already defined in the current context", location());
    }
}

void LocalVariableDefinition::doBuild(CompileContext* context)
{
    variable_->build(context);
}

bool LocalVariableDefinition::accept(ance::ApplicationVisitor& visitor)
{
    return visitor.visitLocalVariableDefinition(*this);
}
