#include "return_statement.h"
#include "Value.h"
#include "Function.h"

return_statement::return_statement(ance::Function* function, const unsigned int l, const unsigned int c, ance::Value* return_value) : Statement(function, l, c), return_value_(return_value)
{
}

void return_statement::build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	get_containing_function()->add_return(return_value_);
}

return_statement::~return_statement() = default;