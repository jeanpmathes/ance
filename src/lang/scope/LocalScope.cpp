#include "LocalScope.h"

#include "lang/ApplicationVisitor.h"

lang::LocalScope::LocalScope(lang::Scope* parent) : Scope(parent) {}

llvm::DIScope* lang::LocalScope::getDebugScope(CompileContext& context) const
{
    return scope()->getDebugScope(context);
}

bool lang::LocalScope::isPartOfFunction() const
{
    return true;
}
