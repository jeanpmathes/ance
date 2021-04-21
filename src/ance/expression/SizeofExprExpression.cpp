#include "SizeofExprExpression.h"

#include "CompileState.h"
#include "ExpressionBackedValue.h"
#include "SizeType.h"

SizeofExprExpression::SizeofExprExpression(Expression* expression, Application& app) : return_value_(new ance::ExpressionBackedValue(this)), return_type_(ance::SizeType::get(app)), expression_(expression)
{
}

ance::Type* SizeofExprExpression::getType()
{
	return return_type_;
}

ance::Value* SizeofExprExpression::getValue()
{
	return  return_value_;
}

llvm::Value* SizeofExprExpression::build(llvm::LLVMContext&, llvm::Module* m, CompileState* state, llvm::IRBuilder<>&, llvm::DIBuilder*)
{
	return ance::SizeType::get(*state->application_)->buildValue(expression_->getType()->getSize(m));
}