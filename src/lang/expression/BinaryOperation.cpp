#include "BinaryOperation.h"

#include "lang/ApplicationVisitor.h"
#include "lang/statement/Statement.h"
#include "validation/ValidationLogger.h"

BinaryOperation::BinaryOperation(Owned<Expression>    left,
                                 lang::BinaryOperator op,
                                 Owned<Expression>    right,
                                 lang::Location       location)
    : Expression(location)
    , left_(std::move(left))
    , op_(op)
    , right_(std::move(right))
{
    addSubexpression(*left_);
    addSubexpression(*right_);
}

Expression const& BinaryOperation::left() const
{
    return *left_;
}

Expression const& BinaryOperation::right() const
{
    return *right_;
}

lang::BinaryOperator BinaryOperation::op() const
{
    return op_;
}

void BinaryOperation::defineType(lang::ResolvingHandle<lang::Type> type)
{
    auto left_type  = left_->type();
    auto right_type = right_->type();

    if (left_type->isDefined() && right_type->isDefined())
    {
        type.reroute(left_type->getOperatorResultType(op_, getRightType(op_, left_type, right_type)));
    }
}

bool BinaryOperation::validate(ValidationLogger& validation_logger) const
{
    bool const valid_operands = left_->validate(validation_logger) && right_->validate(validation_logger);
    if (!valid_operands) return false;

    auto const& left_type  = left_->type();
    auto const& right_type = getRightType();

    if (!left_type.isOperatorDefined(op_, right_type))
    {
        if (lang::Type::areSame(left_->type(), right_->type()))
        {
            validation_logger.logError("Type " + left_->type().getAnnotatedName() + " does not provide operator '"
                                           + op_.toString() + "'",
                                       location());
        }
        else
        {
            validation_logger.logError("Type " + left_->type().getAnnotatedName() + " does not provide operator '"
                                           + op_.toString() + "' with type " + right_->type().getAnnotatedName(),
                                       location());
        }

        return false;
    }
    else if (!lang::Type::areSame(right_type, right_->type()))
    {
        bool const can_convert =
            right_->type().validateImplicitConversion(right_type, right_->location(), validation_logger);
        if (!can_convert) return false;
    }

    return left_type.validateOperator(op_, right_type, left_->location(), right_->location(), validation_logger);
}

Expression::Expansion BinaryOperation::expandWith(Expressions subexpressions, lang::Context&) const
{
    return {Statements(),
            makeOwned<BinaryOperation>(std::move(subexpressions[0]), op_, std::move(subexpressions[1]), location()),
            Statements()};
}

void BinaryOperation::doBuild(CompileContext& context)
{
    Shared<lang::Value> left_value  = left_->getValue();
    Shared<lang::Value> right_value = right_->getValue();

    if (!lang::Type::areSame(right_->type(), getRightType()))
    {
        right_value = right_->type()->buildImplicitConversion(getRightType(), right_value, context);
    }

    Shared<lang::Value> result = left_value->type()->buildOperator(op_, left_value, right_value, context);
    setValue(result);
}

lang::ResolvingHandle<lang::Type> BinaryOperation::getRightType()
{
    return getRightType(op_, left_->type(), right_->type());
}

lang::Type const& BinaryOperation::getRightType() const
{
    return getRightTypeC(op_, left_->type(), right_->type());
}

lang::ResolvingHandle<lang::Type> BinaryOperation::getRightType(lang::BinaryOperator              op,
                                                                lang::ResolvingHandle<lang::Type> left,
                                                                lang::ResolvingHandle<lang::Type> right)
{
    if (lang::Type::areSame(left, right)) return right;

    if (!left->isOperatorDefined(op, right) && left->isOperatorDefined(op, left)
        && right->isImplicitlyConvertibleTo(left))
    {
        return left;
    }

    return right;
}

lang::Type const& BinaryOperation::getRightTypeC(lang::BinaryOperator op,
                                                 lang::Type const&    left,
                                                 lang::Type const&    right)
{
    if (lang::Type::areSame(left, right)) return right;

    if (!left.isOperatorDefined(op, right) && left.isOperatorDefined(op, left) && right.isImplicitlyConvertibleTo(left))
    {
        return left;
    }

    return right;
}

BinaryOperation::~BinaryOperation() = default;
