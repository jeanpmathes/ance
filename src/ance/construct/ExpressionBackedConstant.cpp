#include "ExpressionBackedConstant.h"

ance::ExpressionBackedConstant::ExpressionBackedConstant(BuildableConstantExpression* expression) : expression_(expression)
{
}

ance::Type *ance::ExpressionBackedConstant::getType()
{
    return expression_->getType();
}

llvm::Constant* ance::ExpressionBackedConstant::getConstant(llvm::LLVMContext& c)
{
  return expression_->buildConstant(c);
}
