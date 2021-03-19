#include "sizeof_expression.h"

#include "CompileState.h"
#include "ExpressionValue.h"
#include "SizeType.h"

sizeof_expression::sizeof_expression(Expression* expression, Application& app) : return_value_(new ance::ExpressionValue(this)), return_type_(ance::SizeType::get(app)), expression_(expression)
{
}

ance::Type* sizeof_expression::get_type()
{
	return return_type_;
}

ance::Value* sizeof_expression::get_value()
{
	return  return_value_;
}

llvm::Value* sizeof_expression::build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	return ance::SizeType::get(*state->application)->build_value(expression_->get_type()->get_size(m));
}