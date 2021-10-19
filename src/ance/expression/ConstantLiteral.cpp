#include "ConstantLiteral.h"

#include <utility>

#include "ance/ApplicationVisitor.h"
#include "ance/scope/Scope.h"

ConstantLiteral::ConstantLiteral(std::shared_ptr<ance::Constant> constant, ance::Location location)
    : Expression(location)
    , constant_(std::move(constant))
{}

ance::Type* ConstantLiteral::type()
{
    return constant_->type();
}

bool ConstantLiteral::validate(ValidationLogger&)
{
    return true;
}

std::shared_ptr<ance::Constant> ConstantLiteral::getConstantValue() const
{
    return constant_;
}

bool ConstantLiteral::accept(ance::ApplicationVisitor& visitor)
{
    return visitor.visitConstantLiteral(*this);
}
