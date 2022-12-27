#include "If.h"

#include "lang/ApplicationVisitor.h"
#include "lang/construct/Function.h"
#include "lang/expression/Expression.h"
#include "lang/type/BooleanType.h"
#include "validation/ValidationLogger.h"

If::If(Owned<Expression>          condition,
       Owned<Statement>           if_block,
       Optional<Owned<Statement>> else_block,
       lang::Location             location)
    : Statement(location)
    , condition_(std::move(condition))
    , if_block_(std::move(if_block))
    , else_block_(std::move(else_block))
{
    addSubexpression(*condition_);

    if (if_block_.hasValue()) addSubstatement(*if_block_.value());

    if (else_block_.hasValue()) addSubstatement(*else_block_.value());
}

Expression const& If::condition() const
{
    return *condition_;
}

Statement const* If::ifBlock() const
{
    return getPtr(if_block_);
}

Statement const* If::elseBlock() const
{
    return getPtr(else_block_);
}

std::vector<Owned<lang::BasicBlock>> If::createBasicBlocks(lang::BasicBlock& entry, lang::Function& function)
{
    auto blocks = lang::BasicBlock::createBranching(condition_.get(), getPtr(if_block_), getPtr(else_block_), function);

    entry.link(*blocks.front());

    return blocks;
}

void If::validate(ValidationLogger& validation_logger) const
{
    if (!condition_->validate(validation_logger)) return;

    if (if_block_.hasValue()) if_block_.value()->validate(validation_logger);
    if (else_block_.hasValue()) else_block_.value()->validate(validation_logger);

    lang::Type::checkMismatch(lang::BooleanType::get(), condition_->type(), condition_->location(), validation_logger);
}

Statements If::expandWith(Expressions subexpressions, Statements substatements) const
{
    Statements statements;

    if (!else_block_.hasValue())
    {
        statements.emplace_back(
            makeOwned<If>(std::move(subexpressions[0]), std::move(substatements[0]), std::nullopt, location()));
    }
    else
    {
        statements.emplace_back(makeOwned<If>(std::move(subexpressions[0]),
                                              std::move(substatements[0]),
                                              std::move(substatements[1]),
                                              location()));
    }

    return statements;
}

void If::doBuild(CompileContext&)
{
    // Handled by basic block.
}
