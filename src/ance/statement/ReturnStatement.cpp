#include "ReturnStatement.h"

#include "ance/ApplicationVisitor.h"
#include "ance/construct/DefinedFunction.h"
#include "ance/expression/Expression.h"
#include "ance/scope/LocalScope.h"
#include "ance/type/VoidType.h"
#include "validation/ValidationLogger.h"

ReturnStatement::ReturnStatement(Expression* return_value, ance::Location location)
    : Statement(location)
    , return_value_(return_value)
{
    addChild(*return_value);
}

void ReturnStatement::setFunction(ance::DefinedFunction* function)
{
    return_value_->setContainingScope(function);
}

void ReturnStatement::validate(ValidationLogger& validation_logger)
{
    if (return_value_)
    {
        if (getContainingFunction()->returnType() == ance::VoidType::get())
        {
            validation_logger.logError("Cannot return value in void function '" + getContainingFunction()->name() + "'",
                                       location());
        }
        else if (return_value_->validate(validation_logger))
        {
            ance::Type::checkMismatch(getContainingFunction()->returnType(),
                                      return_value_->type(),
                                      return_value_->location(),
                                      validation_logger);
        }
    }
}

void ReturnStatement::doBuild(CompileContext* context)
{
    ance::Value* return_value = nullptr;

    if (return_value_)
    {
        return_value = return_value_->getValue();
        return_value = ance::Type::makeMatching(getContainingFunction()->returnType(), return_value, context);
    }

    getContainingFunction()->addReturn(return_value);
}

bool ReturnStatement::accept(ance::ApplicationVisitor& visitor)
{
    return visitor.visitReturnStatement(*this);
}
