#include "Statement.h"

Statement::Statement(ance::Location location) : location_(location) {}

void Statement::setContainingFunction(ance::DefinedFunction* function)
{
    assert(!function_);
    function_ = function;

    setFunction(function);
}

void Statement::setFunction(ance::DefinedFunction*) {}

ance::DefinedFunction* Statement::getContainingFunction() const
{
    return function_;
}

ance::Location Statement::location() const
{
    return location_;
}
