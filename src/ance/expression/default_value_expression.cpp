#include "default_value_expression.h"

#include "Value.h"
#include "Constant.h"
#include "Type.h"

#include "ExpressionBackedConstant.h"

default_value_expression::default_value_expression(ance::Type* type) : type_(type), constant_(new ance::ExpressionBackedConstant(this))
{
}

ance::Type* default_value_expression::get_type()
{
	return type_;
}

ance::Value* default_value_expression::get_value()
{
	return constant_;
}

llvm::Value* default_value_expression::build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	return build_constant(c);
}

ance::Constant* default_value_expression::get_constant_value()
{
	return constant_;
}

llvm::Constant* default_value_expression::build_constant(llvm::LLVMContext& c)
{
	return type_->get_default(c);
}

default_value_expression::~default_value_expression() = default;