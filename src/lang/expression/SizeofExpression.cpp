#include "SizeofExpression.h"

#include "lang/ApplicationVisitor.h"
#include "lang/statement/Statement.h"
#include "lang/type/SizeType.h"
#include "lang/type/Type.h"

SizeofExpression::SizeofExpression(Owned<Expression> expression, lang::Location location)
    : Expression(location)
    , expression_(std::move(expression))
{
    addSubexpression(*expression_);
}

Expression const& SizeofExpression::expression() const
{
    return *expression_;
}

void SizeofExpression::defineType(lang::ResolvingHandle<lang::Type> type)
{
    if (!isInitialized()) return;

    type.reroute(scope().context().getSizeType());
}

void SizeofExpression::walkDefinitions()
{
    Expression::walkDefinitions();

    expression_->type();
}

bool SizeofExpression::validate(ValidationLogger& validation_logger) const
{
    return expression_->validate(validation_logger);
}

Expression::Expansion SizeofExpression::expandWith(Expressions subexpressions, lang::Context&) const
{
    return {Statements(), makeOwned<SizeofExpression>(std::move(subexpressions[0]), location()), Statements()};
}
