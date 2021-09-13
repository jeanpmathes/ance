#include "ConstantLiteral.h"

#include "ance/construct/constant/Constant.h"
#include "ance/scope/Scope.h"

ConstantLiteral::ConstantLiteral(ance::Constant* constant, ance::Location location)
    : Expression(location)
    , constant_(constant)
{}

ance::Type* ConstantLiteral::type()
{
    return constant_->type();
}

bool ConstantLiteral::validate(ValidationLogger&)
{
    return true;
}

ance::Constant* ConstantLiteral::getConstantValue() const
{
    return constant_;
}

bool ConstantLiteral::accept(ance::ApplicationVisitor& visitor)
{
    return visitor.visitConstantLiteral(*this);
}
