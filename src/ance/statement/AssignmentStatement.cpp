#include "AssignmentStatement.h"

#include "ance/construct/DefinedFunction.h"
#include "ance/expression/Expression.h"
#include "ance/scope/LocalScope.h"
#include "validation/ValidationLogger.h"

AssignmentStatement::AssignmentStatement(std::unique_ptr<Expression> assignable,
                                         Assigner                    assigner,
                                         std::unique_ptr<Expression> assigned,
                                         ance::Location              location)
    : Statement(location)
    , assignable_(std::move(assignable))
    , assigner_(assigner)
    , assigned_(std::move(assigned))
{
    assert(assigner != Assigner::REFERENCE_BINDING);
}

void AssignmentStatement::setFunction(ance::DefinedFunction* function)
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
