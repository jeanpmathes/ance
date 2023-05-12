#include "Loop.h"

#include "lang/ApplicationVisitor.h"

Loop::Loop(Owned<Statement> block, lang::Location location) : Statement(location), block_(std::move(block))
{
    addSubstatement(*block_);
}

Statement const& Loop::body() const
{
    return *block_;
}

std::vector<Owned<lang::BasicBlock>> Loop::createBasicBlocks(lang::BasicBlock& entry, lang::Function& function)
{
    auto blocks = lang::BasicBlock::createLooping(*block_, &loop_parts_, function);

    entry.link(*blocks.front());

    return blocks;
}

void Loop::validate(ValidationLogger& validation_logger) const
{
    block_->validate(validation_logger);
}

Statements Loop::expandWith(Expressions, Statements substatements, lang::Context&) const
{
    Statements statements;

    statements.emplace_back(makeOwned<Loop>(std::move(substatements[0]), location()));

    return statements;
}

void Loop::doBuild(CompileContext&)
{
    // Handled by basic block.
}

bool Loop::isLoop() const
{
    return true;
}

std::pair<lang::BasicBlock*, lang::BasicBlock*> Loop::getLoopParts() const
{
    return loop_parts_;
}
