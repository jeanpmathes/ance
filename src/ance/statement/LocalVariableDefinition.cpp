#include "LocalVariableDefinition.h"

#include <utility>

#include "DefinedFunction.h"
#include "Expression.h"
#include "LocalScope.h"

LocalVariableDefinition::LocalVariableDefinition(
    std::string identifier,
    ance::Type* type,
    Assigner    assigner,
    Expression* assigned,
    unsigned    l,
    unsigned    c)
    : Statement(l, c), identifier_(std::move(identifier)), type_(type), assigner_(assigner), assigned_(assigned)
{
}

void LocalVariableDefinition::setContainingFunction(ance::DefinedFunction* function)
{
    Statement::setContainingFunction(function);

    variable_ = function->getScope()->defineLocalVariable(identifier_, type_, assigner_, assigned_);
    assigned_->setScope(function->getScope());
}

void LocalVariableDefinition::build(CompileContext* context)
{
    variable_->build(context);
}
