#include "function_call.h"

#include "CompileState.h"
#include "Value.h"

namespace ance {
	class Function;
}

function_call::function_call(std::string identifier, ance::Scope* scope) : scope_(scope), identifier_(identifier), return_value_(new ance::Value(this))
{
}

ance::Type* function_call::get_type()
{
	return scope_->GetFunction(identifier_)->get_return_type();
}

ance::Value* function_call::get_value()
{
	return return_value_;
}

llvm::Value* function_call::build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	ance::Function* fn = state->application->scope()->GetFunction(identifier_);
	return fn->BuildCall(c, m, state, ir, di);
}

function_call::~function_call() = default;