#ifndef LITERAL_EXPRESSION_H
#define LITERAL_EXPRESSION_H

#include "Expression.h"

class literal_expression : public Expression
{
public:
	literal_expression(std::string literal);

	ance::Value* get_value();
	llvm::Value* build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di);

	~literal_expression();

private:
	ance::Value* value_;
	std::string literal_;
};
#endif