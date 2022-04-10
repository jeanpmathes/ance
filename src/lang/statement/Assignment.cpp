#include "Assignment.h"

#include "lang/construct/Function.h"
#include "lang/expression/Expression.h"
#include "lang/scope/LocalScope.h"
#include "validation/ValidationLogger.h"
#include "lang/Assigner.h"

Assignment::Assignment(std::unique_ptr<Expression> assignable,
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

Expression& Assignment::assignable() const
{
    return *assignable_;
}

lang::Assigner Assignment::assigner() const
{
    return assigner_;
}

Expression& Assignment::assigned() const
{
    return *assigned_;
}

void Assignment::setScope(lang::Scope* scope)
{
    assignable_->setContainingScope(scope);
    assigned_->setContainingScope(scope);
}

void Assignment::walkDefinitions()
{
    assignable_->walkDefinitions();
    assigned_->walkDefinitions();
}

void Assignment::validate(ValidationLogger& validation_logger)
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

void Assignment::doBuild(CompileContext* context)
{
    assignable_->assign(assigned_->getValue(), context);
}