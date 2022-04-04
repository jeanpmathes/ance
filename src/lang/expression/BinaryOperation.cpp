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
    addChild(*left_);
    addChild(*right_);
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

void BinaryOperation::setScope(lang::Scope* scope)
{
    left_->setContainingScope(scope);
    right_->setContainingScope(scope);
}

void BinaryOperation::walkDefinitions()
{
    left_->walkDefinitions();
    right_->walkDefinitions();
}

lang::ResolvingHandle<lang::Type> BinaryOperation::type()
{
    return lang::Type::getDereferencedType(left_->type())->getOperatorResultType(op_, right_->type());
}

bool BinaryOperation::validate(ValidationLogger& validation_logger)
{
    bool valid_operands = left_->validate(validation_logger) && right_->validate(validation_logger);
    if (!valid_operands) return false;

    lang::ResolvingHandle<lang::Type> left_type = lang::Type::getDereferencedType(left_->type());

    if (!left_type->isOperatorDefined(op_, right_->type()))
    {
        if (lang::Type::areSame(left_type, right_->type()))
        {
            validation_logger.logError("Type " + left_type->getAnnotatedName() + " does not provide operator '"
                                           + op_.toString() + "'",
                                       location());
        }
        else {
            validation_logger.logError("Type " + left_type->getAnnotatedName() + " does not provide operator '"
                                           + op_.toString() + "' with type " + right_->type()->getAnnotatedName(),
                                       location());
        }

        return false;
    }

    return left_type->validateOperator(op_, right_->type(), left_->location(), right_->location(), validation_logger);
}

void BinaryOperation::doBuild(CompileContext* context)
{
    std::shared_ptr<lang::Value> left_value  = lang::Type::getValueOrDereference(left_->getValue(), context);
    std::shared_ptr<lang::Value> right_value = right_->getValue();

    std::shared_ptr<lang::Value> result = left_value->type()->buildOperator(op_, left_value, right_value, context);
    setValue(result);
}

BinaryOperation::~BinaryOperation() = default;
