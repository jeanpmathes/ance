#include "Parenthesis.h"

#include "lang/ApplicationVisitor.h"
#include "lang/statement/Statement.h"

Parenthesis::Parenthesis(std::unique_ptr<Expression> expression, lang::Location location)
    : Expression(location)
    , expression_(std::move(expression))
{
    addSubexpression(*expression_);
}

Expression& Parenthesis::contained() const
{
    return *expression_;
}

bool Parenthesis::isNamed()
{
    return expression_->isNamed();
}

bool Parenthesis::validate(ValidationLogger& validation_logger) const
{
    return expression_->validate(validation_logger);
}

bool Parenthesis::validateAssignment(std::shared_ptr<lang::Value> const& value,
                                     lang::Location                      value_location,
                                     ValidationLogger&                   validation_logger)
{
    return expression_->validateAssignment(value, value_location, validation_logger);
}

Expression::Expansion Parenthesis::expandWith(Expressions subexpressions) const
{
    return {Statements(), std::make_unique<Parenthesis>(std::move(subexpressions[0]), location()), Statements()};
}

std::optional<lang::ResolvingHandle<lang::Type>> Parenthesis::tryGetType() const
{
    return expression_->tryGetType();
}

std::shared_ptr<lang::Value> Parenthesis::getValue() const
{
    return expression_->getValue();
}

void Parenthesis::doAssign(std::shared_ptr<lang::Value> value, CompileContext& context)
{
    expression_->assign(value, context);
}
