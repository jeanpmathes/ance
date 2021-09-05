#include "AssignmentStatement.h"

#include "ance/assignable/Assignable.h"
#include "ance/construct/DefinedFunction.h"
#include "ance/expression/Expression.h"
#include "ance/scope/LocalScope.h"

AssignmentStatement::AssignmentStatement(Assignable* assignable, Expression* assigned, ance::Location location)
    : Statement(location)
    , assignable_(assignable)
    , assigned_(assigned)
{
    assignable_->assign(assigned->getValue(), assigned->location());
}

void AssignmentStatement::setFunction(ance::DefinedFunction* function)
{
    assignable_->setContainingScope(function);
    assigned_->setContainingScope(function);
}

void AssignmentStatement::validate(ValidationLogger& validation_logger)
{
    if (assigned_->validate(validation_logger)) { assignable_->validate(validation_logger); }
}

void AssignmentStatement::doBuild(CompileContext* context)
{
    assignable_->build(context);
}
