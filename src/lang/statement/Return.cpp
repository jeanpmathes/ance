#include "Return.h"

#include "lang/ApplicationVisitor.h"
#include "lang/construct/Function.h"
#include "lang/expression/Expression.h"
#include "validation/ValidationLogger.h"

Return::Return(Optional<Owned<Expression>> return_value, lang::Location location)
    : Statement(location)
    , return_value_(std::move(return_value))
{
    if (return_value_.hasValue()) addSubexpression(*return_value_.value());
}

Expression const* Return::expression() const
{
    return return_value_.value().get();
}

std::vector<Owned<lang::BasicBlock>> Return::createBasicBlocks(lang::BasicBlock& entry, lang::Function& function)
{
    std::vector<Owned<lang::BasicBlock>> blocks;
    blocks.push_back(
        lang::BasicBlock::createReturning(scope()->asLocalScope(), return_value_.value().get(), location(), function));

    entry.link(*blocks.front());

    return blocks;
}

void Return::validate(ValidationLogger& validation_logger) const
{
    if (return_value_.hasValue()) return_value_.value()->validate(validation_logger);
}

Statements Return::expandWith(Expressions subexpressions, Statements) const
{
    Statements statements;

    if (return_value_.hasValue())
    {
        statements.emplace_back(makeOwned<Return>(std::move(subexpressions[0]), location()));
    }
    else { statements.emplace_back(makeOwned<Return>(std::nullopt, location())); }

    return statements;
}

void Return::doBuild(CompileContext&)
{
    // Handled by basic block.
}
