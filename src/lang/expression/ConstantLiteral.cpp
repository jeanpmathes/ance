#include "ConstantLiteral.h"

#include <utility>

#include "lang/scope/Scope.h"

ConstantLiteral::ConstantLiteral(std::shared_ptr<lang::Constant> constant, lang::Location location)
    : Expression(location)
    , constant_(std::move(constant))
{}

lang::ResolvingHandle<lang::Type> ConstantLiteral::type()
{
    return constant_->type();
}

bool ConstantLiteral::validate(ValidationLogger& validation_logger)
{
    return constant_->validate(validation_logger, location());
}

std::shared_ptr<lang::Constant> ConstantLiteral::getConstantValue() const
{
    return constant_;
}
