#include "StructScope.h"

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"

lang::StructScope::StructScope(Scope& parent, lang::ResolvingHandle<lang::Type> self) : Scope(&parent), self_(self) {}

bool lang::StructScope::isPartOfFunction() const
{
    return false;
}

llvm::DIScope* lang::StructScope::getDebugScope(CompileContext& context) const
{
    return self_->getDebugType(context);
}
