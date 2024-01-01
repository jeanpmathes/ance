#include "NoValue.h"

#include <utility>

#include "lang/ApplicationVisitor.h"

lang::NoValue::NoValue(Passed<UnexpandedExpression> unexpanded_expression)
    : unexpanded_expression_(std::move(unexpanded_expression))
{}

lang::ResolvingHandle<lang::Type> lang::NoValue::type()
{
    return unexpanded_expression_->type();
}

lang::Type const& lang::NoValue::type() const
{
    return unexpanded_expression_->type();
}

void lang::NoValue::buildNativeValue(CompileContext&)
{
    throw std::logic_error("Cannot build value provided by unexpanded expression");
}

void lang::NoValue::buildContentValue(CompileContext&)
{
    throw std::logic_error("Cannot build value provided by unexpanded expression");
}
