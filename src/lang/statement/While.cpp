#include "While.h"

#include "lang/construct/Function.h"
#include "lang/expression/Expression.h"
#include "validation/ValidationLogger.h"
#include "lang/type/BooleanType.h"

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

void While::validate(ValidationLogger& validation_logger)
{
    if (!condition_->validate(validation_logger)) return;

    block_->validate(validation_logger);

    lang::Type::checkMismatch(lang::BooleanType::get(), condition_->type(), condition_->location(), validation_logger);
}

Statements While::expandWith(Expressions subexpressions, Statements substatements) const
{
    Statements statements;

    statements.push_back(
        std::make_unique<While>(std::move(subexpressions[0]), std::move(substatements[0]), location()));

    return statements;
}

void While::doBuild(CompileContext*)
{
    // Handled by basic block.
}
