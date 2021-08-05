#include "AssignmentStatement.h"

#include "ance/assignable/Assignable.h"
#include "ance/construct/DefinedFunction.h"
#include "ance/expression/Expression.h"
#include "ance/scope/LocalScope.h"

AssignmentStatement::AssignmentStatement(Assignable*  assignable,
                                         Expression*  assigned,
                                         ance::Location location)
    : Statement(location)
    , assignable_(assignable)
    , assigned_(assigned)
{}

void AssignmentStatement::setFunction(ance::DefinedFunction* function)
{
    assignable_->setScope(function);
    assigned_->setScope(function);
}

void AssignmentStatement::build(CompileContext* context)
{
    assignable_->assign(assigned_->getValue(), context);
}
