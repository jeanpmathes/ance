#include "default_value_expression.h"

#include "Value.h"
#include "Constant.h"

default_value_expression::default_value_expression() : constant_(new ance::Constant(this))
{
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
	return llvm::ConstantDataArray::getString(c, "", false);
}

default_value_expression::~default_value_expression() = default;