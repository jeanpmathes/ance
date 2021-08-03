#include "LocalVariableDefinition.h"

#include <utility>

#include "ance/construct/DefinedFunction.h"
#include "ance/expression/Expression.h"
#include "ance/scope/LocalScope.h"

LocalVariableDefinition::LocalVariableDefinition(std::string identifier,
                                                 ance::Type* type,
                                                 Assigner    assigner,
                                                 Expression* assigned,
                                                 unsigned    line,
                                                 unsigned    column)
    : Statement(line, column)
    , identifier_(std::move(identifier))
    , type_(type)
    , assigner_(assigner)
    , assigned_(assigned)
{}

void LocalVariableDefinition::setFunction(ance::DefinedFunction* function)
{
    variable_ =
        function->getFunctionScope()->defineAutoVariable(identifier_, type_, assigner_, assigned_->getValue(), line());
    assigned_->setScope(function);
}

void LocalVariableDefinition::build(CompileContext* context)
{
    variable_->build(context);
}
