#include "UnexpandedExpression.h"

#include "lang/ApplicationVisitor.h"
#include "lang/construct/value/NoValue.h"

UnexpandedExpression::UnexpandedExpression(lang::Location location)
    : Expression(location)
    , value_(makeShared<lang::NoValue>(pass(*this)))
{}

Shared<lang::Value> UnexpandedExpression::getValue()
{
    return value_;
}

lang::Value const& UnexpandedExpression::getValue() const
{
    return *value_;
}
