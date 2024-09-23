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
    auto blocks = lang::BasicBlock::createBranching(*condition_, **if_block_, getPtr(else_block_), function);

    entry.link(*blocks.front());

    return blocks;
}

bool If::validate(ValidationLogger& validation_logger) const
{
    if (!condition_->validate(validation_logger)) return false;

    bool valid = true;

    if (if_block_.hasValue()) valid &= if_block_.value()->validate(validation_logger);
    if (else_block_.hasValue()) valid &= else_block_.value()->validate(validation_logger);

    valid &= lang::Type::checkMismatch(scope().context().getBooleanType(),
                                       condition_->type(),
                              condition_->location(),
                              validation_logger);

    return valid;
}

Statements If::expandWith(Expressions subexpressions, Statements substatements, lang::Context&) const
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
