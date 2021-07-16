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
    unsigned    line,
    unsigned    column)
    : Statement(line, column), identifier_(std::move(identifier)), type_(type), assigner_(assigner), assigned_(assigned)
{
}

void LocalVariableDefinition::setFunction(ance::DefinedFunction* function)
{
    variable_ = function->getScope()->defineLocalVariable(identifier_, type_, assigner_, assigned_);
    assigned_->setScope(function->getScope());
}

void LocalVariableDefinition::build(CompileContext* context)
{
    variable_->build(context);
}
