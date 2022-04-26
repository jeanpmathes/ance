#include "Return.h"

#include "lang/construct/Function.h"
#include "lang/expression/Expression.h"
#include "validation/ValidationLogger.h"

Return::Return(std::unique_ptr<Expression> return_value, lang::Location location)
    : Statement(location)
    , return_value_(std::move(return_value))
{
    if (return_value_) addSubexpression(*return_value_);
}

Expression* Return::expression()
{
    return return_value_.get();
}

std::vector<std::unique_ptr<lang::BasicBlock>> Return::createBasicBlocks(lang::BasicBlock& entry,
                                                                         lang::Function*   function)
{
    std::vector<std::unique_ptr<lang::BasicBlock>> blocks;
    blocks.push_back(lang::BasicBlock::createReturning(return_value_.get(), location(), function));

    entry.link(*blocks.front());

    return blocks;
}

void Return::validate(ValidationLogger&)
{
    // Handled by basic block.
}

Statements Return::expandWith(Expressions subexpressions, Statements) const
{
    Statements statements;

    if (return_value_) { statements.push_back(std::make_unique<Return>(std::move(subexpressions[0]), location())); }
    else {
        statements.push_back(std::make_unique<Return>(nullptr, location()));
    }

    return statements;
}

void Return::doBuild(CompileContext*)
{
    // Handled by basic block.
}