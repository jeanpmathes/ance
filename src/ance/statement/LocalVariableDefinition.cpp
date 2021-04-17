#include "LocalVariableDefinition.h"

#include "Expression.h"
#include "Function.h"
#include "LocalScope.h"

LocalVariableDefinition::LocalVariableDefinition(ance::Function* function, unsigned l, unsigned c, ance::LocalVariable* variable) :
	Statement(function, l, c), variable_(variable)
{
}

void LocalVariableDefinition::build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	variable_->build(c, m, state, ir, di);
}