#include "While.h"

#include "lang/ApplicationVisitor.h"
#include "lang/construct/Function.h"
#include "lang/expression/Expression.h"
#include "lang/type/BooleanType.h"
#include "validation/ValidationLogger.h"

While::While(Owned<Expression> condition, Owned<Statement> block, lang::Location location)
    : Statement(location)
    , condition_(std::move(condition))
    , block_(std::move(block))
{
    addSubexpression(*condition_);
    addSubstatement(*block_);
}

Expression const& While::condition() const
{
    return *condition_;
}

Statement const& While::body() const
{
    return *block_;
}

std::vector<Owned<lang::BasicBlock>> While::createBasicBlocks(lang::BasicBlock& entry, lang::Function& function)
{
    auto blocks = lang::BasicBlock::createLooping(*condition_, *block_, &loop_parts_, function);

    entry.link(*blocks.front());

    return blocks;
}

void While::validate(ValidationLogger& validation_logger) const
{
    if (!condition_->validate(validation_logger)) return;

    block_->validate(validation_logger);

    lang::Type::checkMismatch(scope()->context().getBooleanType(),
                              condition_->type(),
                              condition_->location(),
                              validation_logger);
}

Statements While::expandWith(Expressions subexpressions, Statements substatements, lang::Context&) const
{
    Statements statements;

    statements.emplace_back(makeOwned<While>(std::move(subexpressions[0]), std::move(substatements[0]), location()));

    return statements;
}

void While::doBuild(CompileContext&)
{
    // Handled by basic block.
}

bool While::isLoop() const
{
    return true;
}

std::pair<lang::BasicBlock*, lang::BasicBlock*> While::getLoopParts() const
{
    return loop_parts_;
}
