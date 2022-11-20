#include "Continue.h"

#include "lang/ApplicationVisitor.h"
#include "validation/ValidationLogger.h"

Continue::Continue(lang::Location location) : Statement(location) {}

void Continue::validate(ValidationLogger& validation_logger) const
{
    if (getLoopParent() == nullptr) { validation_logger.logError("No loop to continue", location()); }
}

std::vector<std::unique_ptr<lang::BasicBlock>> Continue::createBasicBlocks(lang::BasicBlock& entry, lang::Function&)
{
    Statement const* loop_parent = getLoopParent();
    assert(loop_parent != nullptr);

    std::vector<lang::Scope*> scopes;
    lang::Scope*              current = scope();

    while (current != loop_parent->scope())
    {
        scopes.push_back(current);
        current = current->scope();
    }

    auto const& [start, end] = loop_parent->getLoopParts();

    return lang::BasicBlock::createJump(entry, *start, scopes);
}

Statements Continue::expandWith(Expressions, Statements) const
{
    Statements statements;

    statements.push_back(std::make_unique<Continue>(location()));

    return statements;
}

void Continue::doBuild(CompileContext&)
{
    // Is handled trough basic blocks.
}

Statement const* Continue::getLoopParent() const
{
    Statement const* loop_parent = parent();
    while (loop_parent != nullptr && not loop_parent->isLoop()) { loop_parent = loop_parent->parent(); }

    return loop_parent;
}
