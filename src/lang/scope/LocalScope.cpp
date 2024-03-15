#include "LocalScope.h"

#include "lang/ApplicationVisitor.h"

lang::LocalScope::LocalScope(lang::Scope* parent, lang::CodeBlock& code_block) : Scope(parent), code_block_(code_block)
{}

bool lang::LocalScope::isPartOfFunction() const
{
    return true;
}
void lang::LocalScope::resolveFollowingOrder()
{
    for (auto sub_scope : code_block_.getSubScopesInOrder()) { sub_scope.get().resolve(); }
}

void lang::LocalScope::buildEntityDeclarationsFollowingOrder(CompileContext& context) const
{
    for (auto sub_scope : code_block_.getSubScopesInOrder()) { sub_scope.get().buildEntityDeclarations(context); }
}
