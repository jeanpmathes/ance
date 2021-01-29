#ifndef DEFAULT_VALUE_EXPRESSION_H
#define DEFAULT_VALUE_EXPRESSION_H

#include "ConstantExpression.h"

class default_value_expression : public ConstantExpression
{
public:
	default_value_expression(ance::Type* type);

	ance::Type* get_type() override;

	ance::Value* get_value();
	llvm::Value* build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di);

	ance::Constant* get_constant_value();
	llvm::Constant* build_constant(llvm::LLVMContext& c);

	~default_value_expression();

private:
	ance::Type* type_;
	ance::Constant* constant_;
};

#endif