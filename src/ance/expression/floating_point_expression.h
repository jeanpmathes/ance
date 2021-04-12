#ifndef FLOATING_POINT_EXPRESSION_H
#define FLOATING_POINT_EXPRESSION_H

#include "BuildableConstantExpression.h"

namespace ance {
	class FloatingPointType;
}

class floating_point_expression : public BuildableConstantExpression
{
public:
	floating_point_expression(ance::FloatingPointType* type, llvm::APFloat number);

	ance::Type* get_type() override;

	ance::Value* get_value() override;
	llvm::Value* build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di) override;

	ance::Constant* get_constant_value() override;
	llvm::Constant* build_constant(llvm::LLVMContext& c) override;

private:
	ance::FloatingPointType* type_;
	llvm::APFloat number_;
	ance::Constant* constant_;
};

#endif