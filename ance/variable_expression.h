#ifndef VARIABLE_EXPRESSION_H
#define VARIABLE_EXPRESSION_H

#include "Expression.h"

namespace ance {
	class Scope;
}

class variable_expression : public Expression
{
public:
	variable_expression(ance::Scope* scope, std::string identifier);

	ance::Value* get_value();
	llvm::Value* build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di);

	~variable_expression();

private:
	ance::Scope* scope_;
	std::string identifier_;
	ance::Value* value_;
};
#endif