#ifndef ANCE_SRC_ANCE_EXPRESSION_INTEGER_EXPRESSION_H_
#define ANCE_SRC_ANCE_EXPRESSION_INTEGER_EXPRESSION_H_

#include "BuildableConstantExpression.h"

namespace ance {
	class Scope;
}

class integer_expression : public BuildableConstantExpression
{
public:
	integer_expression(llvm::APInt integer, ance::Scope* scope, uint64_t bit_size, bool is_signed);

	ance::Type* get_type() override;

	ance::Value* get_value() override;
	llvm::Value* build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di) override;

	ance::Constant* get_constant_value() override;
	llvm::Constant* build_constant(llvm::LLVMContext& c) override;

	~integer_expression();

private:
	ance::Type* type_;
	ance::Constant* constant_;
	llvm::APInt integer_;
};

#endif
