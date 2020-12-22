#include "literal_expression.h"

literal_expression::literal_expression(std::string literal) : value_(new ance::Value(this)), literal_(literal)
{
}

ance::Value* literal_expression::get_value()
{
	return value_;
}

llvm::Value* literal_expression::build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	return llvm::ConstantDataArray::getString(c, literal_, true);
}

literal_expression::~literal_expression() = default;