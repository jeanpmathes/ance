#include "local_variable_definition.h"

#include "Expression.h"
#include "Function.h"
#include "LocalScope.h"

local_variable_definition::local_variable_definition(ance::Function* function, unsigned l, unsigned c, ance::LocalVariable* variable) :
	Statement(function, l, c), variable_(variable)
{
}

void local_variable_definition::build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	variable_->build(c, m, state, ir, di);
}