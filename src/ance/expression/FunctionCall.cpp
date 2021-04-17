#include "FunctionCall.h"

#include "CompileState.h"
#include "ExpressionBackedValue.h"
#include "Function.h"
#include "GlobalScope.h"
#include "Value.h"

namespace ance {
	class Function;
}

FunctionCall::FunctionCall(std::string identifier, ance::Scope* scope, std::vector<Expression*> arguments) : scope_(scope), identifier_(identifier), return_value_(new ance::ExpressionBackedValue(this)), arguments_(arguments)
{
}

ance::Type* FunctionCall::getType()
{
	return scope_->getGlobalScope()->getFunction(identifier_)->getReturnType();
}

ance::Value* FunctionCall::getValue()
{
	return return_value_;
}

llvm::Value* FunctionCall::build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	ance::Function* fn = state->application_->globalScope()->getFunction(identifier_);

	std::vector<ance::Value*> arg_values;

	for (auto* arg : arguments_)
	{
		arg_values.push_back(arg->getValue());
	}

	return fn->buildCall(arg_values, c, m, state, ir, di);
}

FunctionCall::~FunctionCall() = default;