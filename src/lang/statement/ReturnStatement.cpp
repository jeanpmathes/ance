#include "ReturnStatement.h"

#include "lang/construct/Function.h"
#include "lang/expression/Expression.h"
#include "lang/scope/LocalScope.h"
#include "validation/ValidationLogger.h"

ReturnStatement::ReturnStatement(std::unique_ptr<Expression> return_value, lang::Location location)
    : Statement(location)
    , return_value_(std::move(return_value))
{}

std::unique_ptr<lang::BasicBlock> ReturnStatement::createBlock()
{
    return lang::BasicBlock::createReturning(return_value_.get());
}

void ReturnStatement::setFunction(lang::Function*)
{
    // Handled by basic block.
}

void ReturnStatement::validate(ValidationLogger&)
{
    /*

    if (return_value_)
    {
        if (getContainingFunction()->returnType()->isVoidType())
        {
            validation_logger.logError("Cannot return value in void function '" + getContainingFunction()->name() + "'",
                                       location());
        }
        else if (return_value_->validate(validation_logger)) {
            lang::Type::checkMismatch(getContainingFunction()->returnType(),
                                      return_value_->type(),
                                      return_value_->location(),
                                      validation_logger);
        }
    }

     */
}

void ReturnStatement::doBuild(CompileContext*)
{
    // Handled by basic block.
}
