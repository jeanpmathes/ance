#include "Statement.h"

Statement::Statement(unsigned int line, unsigned int column)
    : line_(line), column_(column)
{
}

void Statement::setContainingFunction(ance::DefinedFunction* function)
{
    assert(!function_);
    function_ = function;

    setFunction(function);
}

void Statement::setFunction(ance::DefinedFunction*)
{
}


ance::DefinedFunction* Statement::getContainingFunction() const
{
    return function_;
}

unsigned int Statement::line() const
{
    return line_;
}

unsigned int Statement::column() const
{
    return column_;
}