#ifndef FUNCTION_CALL_H
#define FUNCTION_CALL_H

#include "BuildableExpression.h"

namespace ance {
	class Scope;
}

class function_call : public BuildableExpression
{
public:
	function_call(std::string identifier, ance::Scope* scope, std::vector<Expression*> arguments);

	ance::Type* get_type() override;

	ance::Value* get_value() override;
	llvm::Value* build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di);

	~function_call();

private:
	ance::Scope* scope_;
	std::string identifier_;
	std::vector<Expression*> arguments_;
	ance::Value* return_value_;
};
#endif