#include "ExpressionBackedConstant.h"

#include "lang/expression/BackingConstantExpression.h"

lang::ExpressionBackedConstant::ExpressionBackedConstant(BackingConstantExpression* expression)
    : expression_(expression)
{}

std::string lang::ExpressionBackedConstant::toString() const
{
    return "";
}

Expression* lang::ExpressionBackedConstant::getBackingExpression() const
{
    return expression_;
}

lang::ResolvingHandle<lang::Type> lang::ExpressionBackedConstant::type()
{
    return expression_->type();
}

llvm::Constant* lang::ExpressionBackedConstant::buildContent(llvm::Module* m)
{
    expression_->buildConstant(m->getContext());
    return expression_->getContentConstant();
}
