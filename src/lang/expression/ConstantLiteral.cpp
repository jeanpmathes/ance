#include "ConstantLiteral.h"

#include <utility>

#include "lang/scope/Scope.h"
#include "lang/statement/Statement.h"

ConstantLiteral::ConstantLiteral(std::shared_ptr<lang::Constant> constant, lang::Location location)
    : Expression(location)
    , constant_(std::move(constant))
{}

lang::Constant& ConstantLiteral::constant() const
{
    return *constant_;
}

lang::ResolvingHandle<lang::Type> ConstantLiteral::type() const
{
    return constant_->type();
}

bool ConstantLiteral::validate(ValidationLogger& validation_logger) const
{
    return constant_->validate(validation_logger, location());
}

Expression::Expansion ConstantLiteral::expandWith(Expressions) const
{
    return {Statements(), std::make_unique<ConstantLiteral>(constant_, location()), Statements()};
}

std::shared_ptr<lang::Constant> ConstantLiteral::getConstantValue() const
{
    return constant_;
}
