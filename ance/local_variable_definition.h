#pragma once

#include "Statement.h"

namespace ance {
	class LocalVariable;
}

class Expression;

class local_variable_definition : public Statement
{
public:
	local_variable_definition(ance::Function* function, unsigned int l, unsigned int c, ance::LocalVariable* variable);
	void build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di) override;

private:
	ance::LocalVariable* variable_;
};
