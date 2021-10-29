#include "Statement.h"

#include "ance/construct/Function.h"
#include "compiler/CompileContext.h"

Statement::Statement(ance::Location location) : location_(location) {}

void Statement::setContainingFunction(ance::Function* function)
{
    assert(!function_);
    function_ = function;

    setFunction(function);
}

void Statement::setFunction(ance::Function*) {}

ance::Scope* Statement::scope() const
{
    return function_;
}

ance::Function* Statement::getContainingFunction() const
{
    return function_;
}

ance::Location Statement::location() const
{
    return location_;
}

void Statement::build(CompileContext* context)
{
    context->setDebugLocation(location(), getContainingFunction());
    doBuild(context);
    context->resetDebugLocation();
}
