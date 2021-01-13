#include "literal_expression.h"

#include "Value.h"
#include "Constant.h"

literal_expression::literal_expression(std::string literal) : value_(new ance::Value(this)), constant_(new ance::Constant(this)), literal_(literal)
{
}

ance::Value* literal_expression::get_value()
{
	return value_;
}

llvm::Value* literal_expression::build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	return llvm::ConstantDataArray::getString(c, literal_, false);
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