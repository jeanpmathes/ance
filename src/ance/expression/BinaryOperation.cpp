#include "BinaryOperation.h"

#include "validation/ValidationLogger.h"

BinaryOperation::BinaryOperation(std::unique_ptr<Expression> left,
                                 BinaryOperator              op,
                                 std::unique_ptr<Expression> right,
                                 ance::Location              location)
    : Expression(location)
    , left_(std::move(left))
    , op_(op)
    , right_(std::move(right))
{}

void BinaryOperation::setScope(ance::Scope* scope)
{
    left_->setContainingScope(scope);
    right_->setContainingScope(scope);
}

ance::ResolvingHandle<ance::Type> BinaryOperation::type()
{
    return left_->type()->getOperatorResultType(op_, right_->type());
}

bool BinaryOperation::validate(ValidationLogger& validation_logger)
{
    bool valid_operands = left_->validate(validation_logger) && right_->validate(validation_logger);
    if (!valid_operands) return false;

    if (!left_->type()->isOperatorDefined(op_, right_->type()))
    {
        validation_logger.logError("Type " + left_->type()->getAnnotatedName() + " does not provide operator "
                                       + op_.toString() + " with type " + right_->type()->getAnnotatedName(),
                                   location());
        return false;
    }

    return left_->type()->validateOperator(op_,
                                           right_->type(),
                                           left_->location(),
                                           right_->location(),
                                           validation_logger);
}

void BinaryOperation::doBuild(CompileContext* context)
{
    std::shared_ptr<ance::Value> left_value  = left_->getValue();
    std::shared_ptr<ance::Value> right_value = right_->getValue();

    std::shared_ptr<ance::Value> result = left_value->type()->buildOperator(op_, left_value, right_value, context);
    setValue(result);
}

BinaryOperation::~BinaryOperation() = default;
