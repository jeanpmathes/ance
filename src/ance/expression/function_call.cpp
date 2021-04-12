#include "function_call.h"

#include "CompileState.h"
#include "ExpressionBackedValue.h"
#include "Function.h"
#include "GlobalScope.h"
#include "Value.h"

namespace ance {
	class Function;
}

function_call::function_call(std::string identifier, ance::Scope* scope, std::vector<Expression*> arguments) : scope_(scope), identifier_(identifier), return_value_(new ance::ExpressionBackedValue(this)), arguments_(arguments)
{
}

ance::Type* function_call::get_type()
{
	return scope_->get_global_scope()->GetFunction(identifier_)->get_return_type();
}

ance::Value* function_call::get_value()
{
	return return_value_;
}

llvm::Value* function_call::build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	ance::Function* fn = state->application->global_scope()->GetFunction(identifier_);

	std::vector<ance::Value*> arg_values;

	for (auto* arg : arguments_)
	{
		arg_values.push_back(arg->get_value());
	}

	return fn->build_call(arg_values, c, m, state, ir, di);
}

function_call::~function_call() = default;