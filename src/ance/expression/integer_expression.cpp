#include "integer_expression.h"

#include <utility>

#include "Constant.h"
#include "IntegerType.h"

integer_expression::integer_expression(llvm::APInt integer, ance::Scope* scope, uint64_t bit_size, bool is_signed) :
	type_(ance::IntegerType::get(scope, bit_size, is_signed)),
	constant_(new ance::Constant(this)), integer_(std::move(integer))
{
}

ance::Type* integer_expression::get_type()
{
	return type_;
}

ance::Value* integer_expression::get_value()
{
	return constant_;
}

llvm::Value* integer_expression::build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	return build_constant(c);
}

ance::Constant* integer_expression::get_constant_value()
{
	return constant_;
}

llvm::Constant* integer_expression::build_constant(llvm::LLVMContext& c)
{
	return llvm::ConstantInt::get(type_->get_native_type(c), integer_);
}

integer_expression::~integer_expression() = default;