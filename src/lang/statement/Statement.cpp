#include "Statement.h"

#include "lang/construct/Function.h"
#include "compiler/CompileContext.h"
#include "lang/construct/BasicBlock.h"

Statement::Statement(lang::Location location) : location_(location) {}

void Statement::setContainingFunction(lang::Function* function)
{
    assert(!function_);
    function_ = function;

    setFunction(function);
}

std::unique_ptr<lang::BasicBlock> Statement::createBlock()
{
    return lang::BasicBlock::createSimple(this);
}

void Statement::setFunction(lang::Function*) {}

lang::Scope* Statement::scope() const
{
    return function_;
}

lang::Function* Statement::getContainingFunction() const
{
    return function_;
}

lang::Location Statement::location() const
{
    return location_;
}

void Statement::build(CompileContext* context)
{
    context->setDebugLocation(location(), getContainingFunction());
    doBuild(context);
    context->resetDebugLocation();
}
