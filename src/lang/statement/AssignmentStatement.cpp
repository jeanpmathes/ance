#include "AssignmentStatement.h"

#include "lang/construct/Function.h"
#include "lang/expression/Expression.h"
#include "lang/scope/LocalScope.h"
#include "validation/ValidationLogger.h"
#include "lang/Assigner.h"

AssignmentStatement::AssignmentStatement(std::unique_ptr<Expression> assignable,
                                         lang::Assigner              assigner,
                                         std::unique_ptr<Expression> assigned,
                                         lang::Location              location)
    : Statement(location)
    , assignable_(std::move(assignable))
    , assigner_(assigner)
    , assigned_(std::move(assigned))
{
    assert(assigner != lang::Assigner::REFERENCE_BINDING);

    addChild(*assignable_);
    addChild(*assigned_);
}

Expression& AssignmentStatement::assignable() const
{
    return *assignable_;
}

lang::Assigner AssignmentStatement::assigner() const
{
    return assigner_;
}

Expression& AssignmentStatement::assigned() const
{
    return *assigned_;
}

void AssignmentStatement::setFunction(lang::Function* function)
{
    assignable_->setContainingScope(function);
    assigned_->setContainingScope(function);
}

void AssignmentStatement::validate(ValidationLogger& validation_logger)
{
    if (assigner_.isFinal())
    {
        validation_logger.logError("Assignment to declared variable cannot be final", location());
        return;
    }

    if (assigned_->validate(validation_logger))
    {
        assignable_->validateAssignment(assigned_->getValue(), assigned_->location(), validation_logger);
    }
}

void AssignmentStatement::doBuild(CompileContext* context)
{
    assignable_->assign(assigned_->getValue(), context);
}