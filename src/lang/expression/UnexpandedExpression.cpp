#include "UnexpandedExpression.h"

#include "lang/construct/value/NoValue.h"

std::shared_ptr<lang::Value> UnexpandedExpression::getValue() const
{
    return value_;
}

UnexpandedExpression::UnexpandedExpression(lang::Location location)
    : Expression(location)
    , value_(std::make_shared<lang::NoValue>(*this))
{}

