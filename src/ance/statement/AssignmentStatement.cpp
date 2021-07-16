#include "AssignmentStatement.h"

#include "Assignable.h"
#include "DefinedFunction.h"
#include "Expression.h"
#include "LocalScope.h"

AssignmentStatement::AssignmentStatement(
    Assignable*  assignable,
    Expression*  assigned,
    unsigned int l,
    unsigned int c)
    : Statement(l, c), assignable_(assignable), assigned_(assigned)
{
}

void AssignmentStatement::setFunction(ance::DefinedFunction* function)
{
    assignable_->setScope(function->getScope());
    assigned_->setScope(function->getScope());
}

void AssignmentStatement::build(CompileContext* context)
{
    assignable_->assign(assigned_->getValue(), context);
}
