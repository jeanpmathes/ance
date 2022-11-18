#include "Continue.h"

#include "lang/ApplicationVisitor.h"

Continue::Continue(lang::Location location) : Statement(location) {}

void Continue::validate(ValidationLogger& validation_logger) const
{
    (void) validation_logger;
    // todo
}

std::vector<std::unique_ptr<lang::BasicBlock>> Continue::createBasicBlocks(lang::BasicBlock& entry, lang::Function&)
{
    Statement const* loop_parent = parent();
    while (not loop_parent->isLoop()) { loop_parent = loop_parent->parent(); }

    auto const& [start, end] = loop_parent->getLoopParts();

    return lang::BasicBlock::createJump(entry, *start);
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
