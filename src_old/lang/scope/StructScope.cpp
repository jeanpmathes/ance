#include "StructScope.h"

#include <utility>

#include "lang/ApplicationVisitor.h"

lang::StructScope::StructScope(Scope& parent, lang::ResolvingHandle<lang::Type> self)
    : Scope(&parent)
    , self_(std::move(self))
{}

bool lang::StructScope::isPartOfFunction() const
{
    return false;
}
