#include "Break.h"

#include "lang/ApplicationVisitor.h"

Break::Break(lang::Location location) : Statement(location) {}

void Break::validate(ValidationLogger& validation_logger) const
{
    (void) validation_logger;
    // todo
}

std::vector<std::unique_ptr<lang::BasicBlock>> Break::createBasicBlocks(lang::BasicBlock& entry, lang::Function&)
{
    Statement const* loop_parent = parent();
    while (not loop_parent->isLoop()) { loop_parent = loop_parent->parent(); }

    auto const& [start, end] = loop_parent->getLoopParts();

    return lang::BasicBlock::createJump(entry, *end);
}

Statements Break::expandWith(Expressions, Statements) const
{
    Statements statements;

    statements.push_back(std::make_unique<Break>(location()));

    return statements;
}

void Break::doBuild(CompileContext&)
{
    // Is handled trough basic blocks.
}
