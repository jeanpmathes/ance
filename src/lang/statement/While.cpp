#include "While.h"

#include "lang/construct/Function.h"
#include "lang/expression/Expression.h"
#include "validation/ValidationLogger.h"

While::While(std::unique_ptr<Expression> condition, std::unique_ptr<Statement> block, lang::Location location)
    : Statement(location)
    , condition_(std::move(condition))
    , block_(std::move(block))
{
    addSubexpression(*condition_);
    addSubstatement(*block_);
}

Expression& While::condition()
{
    return *condition_;
}

std::vector<std::unique_ptr<lang::BasicBlock>> While::createBasicBlocks(lang::BasicBlock& entry,
                                                                        lang::Function*   function)
{
    auto blocks = lang::BasicBlock::createLooping(condition_.get(), block_.get(), function);

    entry.link(*blocks.front());

    return blocks;
}

void While::validate(ValidationLogger&)
{
    // Handled by basic block.
}

void While::doBuild(CompileContext*)
{
    // Handled by basic block.
}
