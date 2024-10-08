#include "Break.h"

#include "lang/ApplicationVisitor.h"
#include "validation/ValidationLogger.h"

Break::Break(lang::Location location) : Statement(location) {}

bool Break::validate(ValidationLogger& validation_logger) const
{
    if (getLoopParent() == nullptr)
    {
        validation_logger.logError("No loop to break", location());
        return false;
    }

    return true;
}

std::vector<Owned<lang::BasicBlock>> Break::createBasicBlocks(lang::BasicBlock& entry, lang::Function&)
{
    Statement const* loop_parent = getLoopParent();
    assert(loop_parent != nullptr);

    std::vector<lang::Scope*> scopes;
    lang::Scope*              current = &scope();

    while (current != &loop_parent->scope())
    {
        scopes.push_back(current);
        current = &current->scope();
    }

    auto const& [start, end] = loop_parent->getLoopParts();

    return lang::BasicBlock::createJump(entry, *end, scopes);
}

Statements Break::expandWith(Expressions, Statements, lang::Context&) const
{
    Statements statements;

    statements.emplace_back(makeOwned<Break>(location()));

    return statements;
}

Statement const* Break::getLoopParent() const
{
    Statement const* loop_parent = parent();
    while (loop_parent != nullptr && not loop_parent->isLoop()) { loop_parent = loop_parent->parent(); }

    return loop_parent;
}
