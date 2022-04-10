#include "Return.h"

#include "lang/construct/Function.h"
#include "lang/expression/Expression.h"
#include "validation/ValidationLogger.h"

Return::Return(std::unique_ptr<Expression> return_value, lang::Location location)
    : Statement(location)
    , return_value_(std::move(return_value))
{
    if (return_value_) addChild(*return_value_);
}

Expression* Return::expression()
{
    return return_value_.get();
}

std::vector<std::unique_ptr<lang::BasicBlock>> Return::createBlocks(lang::BasicBlock& entry, lang::Function*)
{
    std::vector<std::unique_ptr<lang::BasicBlock>> blocks;
    blocks.push_back(lang::BasicBlock::createReturning(return_value_.get(), location()));

    entry.link(*blocks.front());

    return blocks;
}

void Return::setScope(lang::Scope* scope)
{
    if (return_value_) return_value_->setContainingScope(scope);
}

void Return::walkDefinitions()
{
    if (return_value_) return_value_->walkDefinitions();
}

void Return::validate(ValidationLogger&)
{
    // Handled by basic block.
}

void Return::doBuild(CompileContext*)
{
    // Handled by basic block.
}