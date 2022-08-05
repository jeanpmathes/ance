#include "UnaryOperation.h"

#include "validation/ValidationLogger.h"
#include "lang/statement/Statement.h"

UnaryOperation::UnaryOperation(lang::UnaryOperator op, std::unique_ptr<Expression> operand, lang::Location location)
    : Expression(location)
    , operand_(std::move(operand))
    , op_(op)
{
    addSubexpression(*operand_);
}

Expression& UnaryOperation::operand() const
{
    return *operand_;
}

lang::UnaryOperator UnaryOperation::op() const
{
    return op_;
}

std::optional<lang::ResolvingHandle<lang::Type>> UnaryOperation::tryGetType() const
{
    auto operand_type_opt = operand_->tryGetType();
    if (!operand_type_opt) return std::nullopt;
    auto operand_type = *operand_type_opt;

    return operand_type->getOperatorResultType(op_);
}

bool UnaryOperation::validate(ValidationLogger& validation_logger) const
{
    if (!operand_->validate(validation_logger)) return false;

    if (!operand_->type()->isOperatorDefined(op_))
    {
        validation_logger.logError("Type " + operand_->type()->getAnnotatedName() + " does not provide operator '"
                                       + op_.toString() + "'",
                                   location());

        return false;
    }

    return operand_->type()->validateOperator(op_, operand_->location(), validation_logger);
}

Expression::Expansion UnaryOperation::expandWith(Expressions subexpressions) const
{
    return {Statements(),
            std::make_unique<UnaryOperation>(op_, std::move(subexpressions[0]), location()),
            Statements()};
}

void UnaryOperation::doBuild(CompileContext* context)
{
    std::shared_ptr<lang::Value> value = operand_->getValue();

    std::shared_ptr<lang::Value> result = operand_->type()->buildOperator(op_, value, context);
    setValue(result);
}

UnaryOperation::~UnaryOperation() = default;
