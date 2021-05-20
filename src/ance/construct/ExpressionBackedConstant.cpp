#include "ExpressionBackedConstant.h"

ance::ExpressionBackedConstant::ExpressionBackedConstant(BuildableConstantExpression* expression)
	: expression_(
	expression
)
{
}

ance::Type* ance::ExpressionBackedConstant::getType()
{
	return expression_->getType();
}

void ance::ExpressionBackedConstant::build(llvm::LLVMContext& c)
{
	assert(!constant_);
	constant_ = expression_->buildConstant(c);
}

llvm::Constant * ance::ExpressionBackedConstant::getNativeConstant()
{
	assert(constant_);
	return constant_;
}