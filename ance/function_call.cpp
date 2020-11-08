#include "function_call.h"

function_call::function_call(unsigned int l, unsigned int c, std::string ident) : Statement(l, c), identifier(ident)
{
}

void function_call::build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	ance::Function* fn = state->application->GetFunction(identifier);
	fn->BuildCall(c, m, state, ir, di);
}

function_call::~function_call()
{
}