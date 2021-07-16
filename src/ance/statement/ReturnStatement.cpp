#include "ReturnStatement.h"

#include "DefinedFunction.h"
#include "LocalScope.h"

ReturnStatement::ReturnStatement(
    Expression*        return_value,
    unsigned int line,
    unsigned int column)
    : Statement(line, column), return_value_(return_value)
{
}

void ReturnStatement::setFunction(ance::DefinedFunction* function)
{
    return_value_->setScope(function->getScope());
}

void ReturnStatement::build(CompileContext*)
{
    getContainingFunction()->addReturn(return_value_ ? return_value_->getValue() : nullptr);
}
