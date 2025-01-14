#include "UnaryOperation.h"

#include "lang/ApplicationVisitor.h"
#include "lang/statement/Statement.h"
#include "validation/ValidationLogger.h"

UnaryOperation::UnaryOperation(lang::UnaryOperator op, Owned<Expression> operand, lang::Location location)
    : Expression(location)
    , operand_(std::move(operand))
    , op_(op)
{
    addSubexpression(*operand_);
}

Expression const& UnaryOperation::operand() const
{
    return *operand_;
}

lang::UnaryOperator UnaryOperation::op() const
{
    return op_;
}

void UnaryOperation::defineType(lang::ResolvingHandle<lang::Type> type)
{
    auto operand_type = operand_->type();
    if (operand_type->isDefined()) { type.reroute(operand_type->getOperatorResultType(op_)); }
}

bool UnaryOperation::validate(ValidationLogger& validation_logger) const
{
    if (!operand_->validate(validation_logger)) return false;

    if (!operand_->type().isOperatorDefined(op_))
    {
        validation_logger.logError("Type " + operand_->type().getAnnotatedName() + " does not provide operator '"
                                       + op_.toString() + "'",
                                   location());

        return false;
    }

    return operand_->type().validateOperator(op_, operand_->location(), validation_logger);
}

Expression::Expansion UnaryOperation::expandWith(Expressions subexpressions, lang::Context&) const
{
    return {Statements(), makeOwned<UnaryOperation>(op_, std::move(subexpressions[0]), location()), Statements()};
}

UnaryOperation::~UnaryOperation() = default;
