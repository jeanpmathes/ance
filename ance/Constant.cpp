#include "Constant.h"

ance::Constant::Constant(ConstantExpression* expression) : expression_(expression)
{
}

llvm::Constant* ance::Constant::get_constant(llvm::LLVMContext& c)
{
	return expression_->build_constant(c);
}