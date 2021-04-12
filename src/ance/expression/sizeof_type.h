#ifndef SIZEOF_TYPE_H
#define SIZEOF_TYPE_H

#include "BuildableExpression.h"

class Application;

class sizeof_type : public BuildableExpression
{
public:
	sizeof_type(ance::Type* type, Application& app);

	ance::Type* get_type() override;

	ance::Value* get_value() override;
	llvm::Value* build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di) override;

private:
	ance::Value* return_value_;
	ance::Type* return_type_;
	ance::Type* type_;
};

#endif