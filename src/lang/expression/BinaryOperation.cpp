#include "BinaryOperation.h"

#include "validation/ValidationLogger.h"

BinaryOperation::BinaryOperation(std::unique_ptr<Expression> left,
                                 lang::BinaryOperator        op,
                                 std::unique_ptr<Expression> right,
                                 lang::Location              location)
    : Expression(location)
    , left_(std::move(left))
    , op_(op)
    , right_(std::move(right))
{
    addSubexpression(*left_);
    addSubexpression(*right_);
}

Expression& BinaryOperation::left() const
{
    return *left_;
}

Expression& BinaryOperation::right() const
{
    return *right_;
}

lang::BinaryOperator BinaryOperation::op() const
{
    return op_;
}

lang::ResolvingHandle<lang::Type> BinaryOperation::type()
{
    return left_->type()->getOperatorResultType(op_, right_->type());
}

bool BinaryOperation::validate(ValidationLogger& validation_logger)
{
    bool valid_operands = left_->validate(validation_logger) && right_->validate(validation_logger);
    if (!valid_operands) return false;

    if (!left_->type()->isOperatorDefined(op_, right_->type()))
    {
        if (lang::Type::areSame(left_->type(), right_->type()))
        {
            validation_logger.logError("Type " + left_->type()->getAnnotatedName() + " does not provide operator '"
                                           + op_.toString() + "'",
                                       location());
        }
        else {
            validation_logger.logError("Type " + left_->type()->getAnnotatedName() + " does not provide operator '"
                                           + op_.toString() + "' with type " + right_->type()->getAnnotatedName(),
                                       location());
        }

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
    std::shared_ptr<lang::Value> left_value  = left_->getValue();
    std::shared_ptr<lang::Value> right_value = right_->getValue();

    std::shared_ptr<lang::Value> result = left_value->type()->buildOperator(op_, left_value, right_value, context);
    setValue(result);
}

BinaryOperation::~BinaryOperation() = default;
