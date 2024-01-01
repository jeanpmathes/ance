#include "StructScope.h"

#include <utility>

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"

lang::StructScope::StructScope(Scope& parent, lang::ResolvingHandle<lang::Type> self)
    : Scope(&parent)
    , self_(std::move(self))
{}

bool lang::StructScope::isPartOfFunction() const
{
    return false;
}

Execution::Scoped lang::StructScope::getDebugScope(CompileContext& context) const
{
    return std::get<Execution::Struct>(self_->getDebugType(context));
}
