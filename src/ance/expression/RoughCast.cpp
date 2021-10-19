#include "RoughCast.h"

#include "ance/ApplicationVisitor.h"
#include "ance/construct/value/RoughlyCastedValue.h"
#include "ance/type/Type.h"

RoughCast::RoughCast(ance::Type* target_type, std::unique_ptr<Expression> expression, ance::Location location)
    : Expression(location)
    , target_type_(target_type)
    , expression_(std::move(expression))
    , return_value_(std::make_shared<ance::RoughlyCastedValue>(target_type, expression_->getValue()))
{
    addChild(*expression_);
}

void RoughCast::setScope(ance::Scope* scope)
{
    expression_->setContainingScope(scope);
}

ance::Type* RoughCast::type()
{
    return target_type_;
}

bool RoughCast::validate(ValidationLogger& validation_logger)
{
    return expression_->validate(validation_logger);
}

std::shared_ptr<ance::Value> RoughCast::getValue() const
{
    return return_value_;
}

bool RoughCast::accept(ance::ApplicationVisitor& visitor)
{
    return visitor.visitRoughCast(*this);
}

RoughCast::~RoughCast() = default;
