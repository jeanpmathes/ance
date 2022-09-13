#include "NoValue.h"

lang::NoValue::NoValue(UnexpandedExpression& unexpanded_expression) : unexpanded_expression_(unexpanded_expression) {}

lang::ResolvingHandle<lang::Type> lang::NoValue::type() const
{
    return unexpanded_expression_.type();
}

void lang::NoValue::buildNativeValue(CompileContext&)
{
    throw std::logic_error("Cannot build value provided by unexpanded expression.");
}

void lang::NoValue::buildContentValue(CompileContext&)
{
    throw std::logic_error("Cannot build value provided by unexpanded expression.");
}

llvm::Value* lang::NoValue::getNativeValue()
{
    throw std::logic_error("Cannot get value provided by unexpanded expression.");
}

llvm::Value* lang::NoValue::getContentValue()
{
    throw std::logic_error("Cannot get value provided by unexpanded expression.");
}

