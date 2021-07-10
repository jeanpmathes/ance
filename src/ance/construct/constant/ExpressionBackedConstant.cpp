#include "ExpressionBackedConstant.h"

ance::ExpressionBackedConstant::ExpressionBackedConstant(BackingConstantExpression* expression)
    : expression_(
        expression)
{
}

ance::Type* ance::ExpressionBackedConstant::getType()
{
    return expression_->getType();
}

llvm::Constant* ance::ExpressionBackedConstant::buildContent(llvm::Module* m)
{
    expression_->buildConstant(m->getContext());
    return expression_->getContentConstant();
}