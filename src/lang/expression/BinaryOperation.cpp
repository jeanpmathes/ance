#include "BinaryOperation.h"

#include "validation/ValidationLogger.h"
#include "lang/statement/Statement.h"

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

lang::ResolvingHandle<lang::Type> BinaryOperation::type() const
{
    return left_->type()->getOperatorResultType(op_, getRightType());
}

bool BinaryOperation::validate(ValidationLogger& validation_logger)
{
    bool valid_operands = left_->validate(validation_logger) && right_->validate(validation_logger);
    if (!valid_operands) return false;

    auto left_type  = left_->type();
    auto right_type = getRightType();

    if (!left_type->isOperatorDefined(op_, right_type))
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
    else if (!lang::Type::areSame(right_type, right_->type())) {
        bool can_convert =
            right_->type()->validateImplicitConversion(right_type, right_->location(), validation_logger);
        if (!can_convert) return false;
    }

    return left_type->validateOperator(op_, right_type, left_->location(), right_->location(), validation_logger);
}

Expression::Expansion BinaryOperation::expandWith(Expressions subexpressions) const
{
    return {
        Statements(),
        std::make_unique<BinaryOperation>(std::move(subexpressions[0]), op_, std::move(subexpressions[1]), location()),
        Statements()};
}

void BinaryOperation::doBuild(CompileContext* context)
{
    std::shared_ptr<lang::Value> left_value  = left_->getValue();
    std::shared_ptr<lang::Value> right_value = right_->getValue();

    if (!lang::Type::areSame(right_->type(), getRightType()))
    {
        right_value = right_->type()->buildImplicitConversion(getRightType(), right_value, context);
    }

    std::shared_ptr<lang::Value> result = left_value->type()->buildOperator(op_, left_value, right_value, context);
    setValue(result);
}

lang::ResolvingHandle<lang::Type> BinaryOperation::getRightType() const
{
    if (lang::Type::areSame(left_->type(), right_->type())) return right_->type();

    if (!left_->type()->isOperatorDefined(op_, right_->type()) && left_->type()->isOperatorDefined(op_, left_->type())
        && right_->type()->isImplicitlyConvertibleTo(left_->type()))
    {
        return left_->type();
    }

    return right_->type();
}

BinaryOperation::~BinaryOperation() = default;
