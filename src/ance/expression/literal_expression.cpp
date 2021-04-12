#include "literal_expression.h"

#include "ExpressionBackedConstant.h"
#include "ArrayType.h"
#include "Value.h"
#include "Constant.h"
#include "IntegerType.h"

literal_expression::literal_expression(std::string literal, ance::Scope* scope) :
	type_(ance::ArrayType::get(scope, ance::IntegerType::get(scope, 8, false), literal.size())),
	constant_(new ance::ExpressionBackedConstant(this)), literal_(literal)
{
}

ance::Type* literal_expression::get_type()
{
	return type_;
}

ance::Value* literal_expression::get_value()
{
	return constant_;
}

llvm::Value* literal_expression::build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	return build_constant(c);
}

ance::Constant* literal_expression::get_constant_value()
{
	return constant_;
}

llvm::Constant* literal_expression::build_constant(llvm::LLVMContext& c)
{
	return llvm::ConstantDataArray::getString(c, literal_, false);
}

literal_expression::~literal_expression() = default;