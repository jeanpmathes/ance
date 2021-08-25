#include "ReturnStatement.h"

#include "ance/construct/DefinedFunction.h"
#include "ance/scope/LocalScope.h"

ReturnStatement::ReturnStatement(Expression* return_value, ance::Location location)
    : Statement(location)
    , return_value_(return_value)
{}

void ReturnStatement::setFunction(ance::DefinedFunction* function)
{
    return_value_->setContainingScope(function);
}

void ReturnStatement::build(CompileContext*)
{
    getContainingFunction()->addReturn(return_value_ ? return_value_->getValue() : nullptr);
}
