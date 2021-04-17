#pragma once

#include "Statement.h"

namespace ance {
	class LocalVariable;
}

class Expression;

class LocalVariableDefinition : public Statement
{
public:
	LocalVariableDefinition(ance::Function* function, unsigned int l, unsigned int c, ance::LocalVariable* variable);
	void build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di) override;

private:
	ance::LocalVariable* variable_;
};
