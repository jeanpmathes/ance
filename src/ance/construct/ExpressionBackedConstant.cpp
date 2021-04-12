#include "ExpressionBackedConstant.h"

ance::ExpressionBackedConstant::ExpressionBackedConstant(BuildableConstantExpression* expression) : expression_(expression)
{
}

ance::Type *ance::ExpressionBackedConstant::get_type()
{
    return expression_->get_type();
}

llvm::Constant* ance::ExpressionBackedConstant::get_constant(llvm::LLVMContext& c)
{
  return expression_->build_constant(c);
}
