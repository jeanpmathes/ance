#ifndef SIZEOF_EXPRESSION_H
#define SIZEOF_EXPRESSION_H

#include "BuildableExpression.h"

class Application;

class sizeof_expression : public BuildableExpression
{
public:
	sizeof_expression(Expression* expression, Application& app);

	ance::Type* get_type() override;

	ance::Value* get_value() override;
	llvm::Value* build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di) override;

private:
	ance::Value* return_value_;
	ance::Type* return_type_;
	Expression* expression_;
};

#endif