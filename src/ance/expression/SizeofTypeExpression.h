#ifndef ANCE_SRC_ANCE_EXPRESSION_SIZEOFTYPEEXPRESSION_H_
#define ANCE_SRC_ANCE_EXPRESSION_SIZEOFTYPEEXPRESSION_H_

#include "BuildableExpression.h"

class Application;

class SizeofTypeExpression : public BuildableExpression
{
public:
	SizeofTypeExpression(ance::Type* type, Application& app);

	ance::Type* getType() override;

	ance::Value* getValue() override;
	llvm::Value* build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di) override;

private:
	ance::Value* return_value_;
	ance::Type* return_type_;
	ance::Type* type_;
};

#endif