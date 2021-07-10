#include "ReturnStatement.h"

#include "DefinedFunction.h"
#include "LocalScope.h"

ReturnStatement::ReturnStatement(
	Expression* return_value,
	const unsigned int l,
	const unsigned int c
)
	: Statement(l, c), return_value_(return_value)
{
}

void ReturnStatement::setContainingFunction(ance::DefinedFunction* function)
{
	Statement::setContainingFunction(function);

	return_value_->setScope(function->getScope());
}

void ReturnStatement::build(CompileContext*)
{
	getContainingFunction()->addReturn(return_value_ ? return_value_->getValue() : nullptr);
}
