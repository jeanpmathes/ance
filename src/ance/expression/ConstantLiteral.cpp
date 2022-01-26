#include "ConstantLiteral.h"

#include <utility>

#include "ance/scope/Scope.h"

ConstantLiteral::ConstantLiteral(std::shared_ptr<ance::Constant> constant, ance::Location location)
    : Expression(location)
    , constant_(std::move(constant))
{}

ance::ResolvingHandle<ance::Type> ConstantLiteral::type()
{
    return constant_->type();
}

bool ConstantLiteral::validate(ValidationLogger& validation_logger)
{
    return constant_->validate(validation_logger, location());
}

std::shared_ptr<ance::Constant> ConstantLiteral::getConstantValue() const
{
    return constant_;
}
