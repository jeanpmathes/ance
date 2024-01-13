#include "LocalScope.h"

#include "lang/ApplicationVisitor.h"

lang::LocalScope::LocalScope(lang::Scope* parent, lang::CodeBlock& code_block) : Scope(parent), code_block_(code_block)
{}

Execution::Scoped lang::LocalScope::getDebugScope(CompileContext& context) const
{
    return scope().getDebugScope(context);
}

bool lang::LocalScope::isPartOfFunction() const
{
    return true;
}
void lang::LocalScope::resolveFollowingOrder()
{
    for (auto sub_scope : code_block_.getSubScopesInOrder()) { sub_scope.get().resolve(); }
}

void lang::LocalScope::buildDeclarationsFollowingOrder(CompileContext& context)
{
    for (auto sub_scope : code_block_.getSubScopesInOrder()) { sub_scope.get().buildDeclarations(context); }
}
