#include "floating_point_expression.h"

#include <utility>

#include "Constant.h"
#include "FloatingPointType.h"

floating_point_expression::floating_point_expression(ance::FloatingPointType* type, llvm::APFloat number)
	: type_(type), number_(std::move(number)), constant_(new ance::Constant(this))
{
}

ance::Type* floating_point_expression::get_type()
{
	return type_;
}

ance::Value* floating_point_expression::get_value()
{
	return get_constant_value();
}

llvm::Value* floating_point_expression::build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	return build_constant(c);
}

ance::Constant* floating_point_expression::get_constant_value()
{
	return constant_;
}

llvm::Constant* floating_point_expression::build_constant(llvm::LLVMContext& c)
{
	return llvm::ConstantFP::get(type_->get_native_type(c), number_);
}