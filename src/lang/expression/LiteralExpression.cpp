#include "LiteralExpression.h"

#include <utility>

#include "lang/ApplicationVisitor.h"
#include "lang/scope/Scope.h"
#include "lang/statement/Statement.h"

LiteralExpression::LiteralExpression(Shared<lang::LiteralConstant> constant, lang::Location location)
    : Expression(location)
    , constant_(std::move(constant))
{}

lang::LiteralConstant const& LiteralExpression::constant() const
{
    return *constant_;
}

Shared<lang::Constant> LiteralExpression::constant(Execution& exec)
{
    return constant_->embed(exec);
}

void LiteralExpression::defineType(lang::ResolvingHandle<lang::Type> type)
{
    type.reroute(constant_->type());
}

bool LiteralExpression::validate(ValidationLogger& validation_logger) const
{
    return constant_->validate(validation_logger, location());
}

Expression::Expansion LiteralExpression::expandWith(Expressions, lang::Context& new_context) const
{
    return {Statements(), makeOwned<LiteralExpression>(constant_->clone(new_context), location()), Statements()};
}

LiteralExpression::~LiteralExpression() = default;
