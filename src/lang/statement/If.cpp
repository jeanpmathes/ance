#include "If.h"

#include "lang/construct/Function.h"
#include "lang/expression/Expression.h"
#include "validation/ValidationLogger.h"
#include "lang/type/BooleanType.h"

If::If(std::unique_ptr<Expression> condition,
       std::unique_ptr<Statement>  if_block,
       std::unique_ptr<Statement>  else_block,
       lang::Location              location)
    : Statement(location)
    , condition_(std::move(condition))
    , if_block_(std::move(if_block))
    , else_block_(std::move(else_block))
{
    addSubexpression(*condition_);

    if (if_block_) addSubstatement(*if_block_);

    if (else_block_) addSubstatement(*else_block_);
}

Expression& If::condition()
{
    return *condition_;
}

std::vector<std::unique_ptr<lang::BasicBlock>> If::createBasicBlocks(lang::BasicBlock& entry, lang::Function* function)
{
    auto blocks = lang::BasicBlock::createBranching(condition_.get(), if_block_.get(), else_block_.get(), function);

    entry.link(*blocks.front());

    return blocks;
}

void If::validate(ValidationLogger& validation_logger)
{
    if (!condition_->validate(validation_logger)) return;

    if (if_block_) if_block_->validate(validation_logger);
    if (else_block_) else_block_->validate(validation_logger);

    lang::Type::checkMismatch(lang::BooleanType::get(), condition_->type(), condition_->location(), validation_logger);
}

Statements If::expandWith(Expressions subexpressions, Statements substatements) const
{
    Statements statements;

    if (!else_block_)
    {
        statements.push_back(
            std::make_unique<If>(std::move(subexpressions[0]), std::move(substatements[0]), nullptr, location()));
    }
    else {
        statements.push_back(std::make_unique<If>(std::move(subexpressions[0]),
                                                  std::move(substatements[0]),
                                                  std::move(substatements[1]),
                                                  location()));
    }

    return statements;
}

void If::doBuild(CompileContext*)
{
    // Handled by basic block.
}