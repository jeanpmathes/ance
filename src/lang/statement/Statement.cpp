#include "Statement.h"

#include "lang/construct/Function.h"
#include "compiler/CompileContext.h"
#include "lang/construct/BasicBlock.h"

Statement::Statement(lang::Location location) : location_(location) {}

void Statement::setContainingScope(lang::Scope* scope)
{
    assert(!containing_scope_);
    containing_scope_ = scope;

    setScope(scope);
}

std::unique_ptr<lang::BasicBlock> Statement::createBlock()
{
    return lang::BasicBlock::createSimple(this);
}

void Statement::setScope(lang::Scope*) {}

lang::Scope* Statement::scope() const
{
    return containing_scope_;
}

lang::Location Statement::location() const
{
    return location_;
}

void Statement::build(CompileContext* context)
{
    context->setDebugLocation(location(), scope());
    doBuild(context);
    context->resetDebugLocation();
}
