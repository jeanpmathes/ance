#include "FunctionCall.h"

#include <utility>

#include "CompileContext.h"
#include "Function.h"
#include "GlobalScope.h"
#include "Value.h"

namespace ance
{
class Function;
}

FunctionCall::FunctionCall(std::string identifier, std::vector<Expression*> arguments)
	: identifier_(std::move(identifier)),
	  arguments_(std::move(arguments))
{
}

void FunctionCall::setScope(ance::Scope* scope)
{
	scope_ = scope;

	for (auto* arg : arguments_)
	{
		arg->setScope(scope);
	}
}

ance::Type* FunctionCall::getType()
{
	return scope_->getGlobalScope()->getFunction(identifier_)->getReturnType();
}

void FunctionCall::buildValue(
	llvm::LLVMContext& c,
	llvm::Module* m,
	CompileContext* state,
	llvm::IRBuilder<>& ir,
	llvm::DIBuilder* di
)
{
	ance::Function* fn = state->application_->globalScope()->getFunction(identifier_);

	std::vector<ance::Value*> arg_values;

	for (auto* arg : arguments_)
	{
		arg_values.push_back(arg->getValue());
	}

	ance::Value* return_value = fn->buildCall(arg_values, c, m, state, ir, di);

	if (return_value != nullptr) // Not every function returns a value.
	{
		setValue(return_value);
	}
}

FunctionCall::~FunctionCall() = default;