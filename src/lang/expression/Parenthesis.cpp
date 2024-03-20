#include "Parenthesis.h"

#include "lang/ApplicationVisitor.h"
#include "lang/statement/Statement.h"

Parenthesis::Parenthesis(Owned<Expression> expression, lang::Location location)
    : Expression(location)
    , expression_(std::move(expression))
{
    addSubexpression(*expression_);
}

Expression const& Parenthesis::contained() const
{
    return *expression_;
}

bool Parenthesis::isNamed() const
{
    return expression_->isNamed();
}

void Parenthesis::defineType(lang::ResolvingHandle<lang::Type> type)
{
    type.reroute(expression_->type());
}

lang::Type const& Parenthesis::assignableType() const
{
    return expression_->assignableType();
}

bool Parenthesis::validate(ValidationLogger& validation_logger) const
{
    return expression_->validate(validation_logger);
}

bool Parenthesis::validateAssignment(lang::Type const& value_type,
                                     lang::Location    value_location,
                                     ValidationLogger& validation_logger) const
{
    return expression_->validateAssignment(value_type, value_location, validation_logger);
}

Expression::Expansion Parenthesis::expandWith(Expressions subexpressions, lang::Context&) const
{
    return {Statements(), makeOwned<Parenthesis>(std::move(subexpressions[0]), location()), Statements()};
}
