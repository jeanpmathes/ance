#include "ConstantLiteral.h"

#include <utility>

#include "lang/ApplicationVisitor.h"
#include "lang/scope/Scope.h"
#include "lang/statement/Statement.h"

ConstantLiteral::ConstantLiteral(Shared<lang::Constant> constant, lang::Location location)
    : Expression(location)
    , constant_(std::move(constant))
{}

lang::Constant const& ConstantLiteral::constant() const
{
    return *constant_;
}

void ConstantLiteral::defineType(lang::ResolvingHandle<lang::Type>& type)
{
    type.reroute(constant_->type());
}

bool ConstantLiteral::validate(ValidationLogger& validation_logger) const
{
    return constant_->validate(validation_logger, location());
}

Expression::Expansion ConstantLiteral::expandWith(Expressions) const
{
    return {Statements(), makeOwned<ConstantLiteral>(constant_->clone(), location()), Statements()};
}

Shared<lang::Constant> ConstantLiteral::getConstantValue()
{
    return constant_;
}

lang::Constant const& ConstantLiteral::getConstantValue() const
{
    return *constant_;
}

ConstantLiteral::~ConstantLiteral() = default;
