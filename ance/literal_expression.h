#ifndef LITERAL_EXPRESSION_H
#define LITERAL_EXPRESSION_H

#include "ConstantExpression.h"

class literal_expression : public ConstantExpression
{
public:
	literal_expression(std::string literal);

	ance::Value* get_value();
	llvm::Value* build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di);

	ance::Constant* get_constant_value();
	llvm::Constant* build_constant(llvm::LLVMContext& c);

	~literal_expression();

private:
	ance::Value* value_;
	ance::Constant* constant_;
	std::string literal_;
};
#endif