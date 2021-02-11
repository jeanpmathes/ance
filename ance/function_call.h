#ifndef FUNCTION_CALL_H
#define FUNCTION_CALL_H

#include "Expression.h"

namespace ance {
	class Scope;
}

class function_call : public Expression
{
public:
	function_call(std::string identifier, ance::Scope* scope);

	ance::Type* get_type() override;

	ance::Value* get_value() override;
	llvm::Value* build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di) override;

	~function_call();

private:
	ance::Scope* scope_;
	std::string identifier_;
	ance::Value* return_value_;
};
#endif