#include "ReturnStatement.h"

#include "lang/construct/Function.h"
#include "lang/expression/Expression.h"
#include "validation/ValidationLogger.h"

ReturnStatement::ReturnStatement(std::unique_ptr<Expression> return_value, lang::Location location)
    : Statement(location)
    , return_value_(std::move(return_value))
{
    if (return_value_) addChild(*return_value_);
}

Expression* ReturnStatement::expression()
{
    return return_value_.get();
}

std::unique_ptr<lang::BasicBlock> ReturnStatement::createBlock()
{
    return lang::BasicBlock::createReturning(return_value_.get(), location());
}

void ReturnStatement::setScope(lang::Scope* scope)
{
    if (return_value_) return_value_->setContainingScope(scope);
}

void ReturnStatement::walkDefinitions()
{
    if (return_value_) return_value_->walkDefinitions();
}

void ReturnStatement::validate(ValidationLogger&)
{
    // Handled by basic block.
}

void ReturnStatement::doBuild(CompileContext*)
{
    // Handled by basic block.
}
