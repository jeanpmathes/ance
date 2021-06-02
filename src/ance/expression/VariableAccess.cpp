#include "VariableAccess.h"

#include <utility>

#include "Value.h"
#include "Scope.h"

VariableAccess::VariableAccess(std::string identifier)
	: identifier_(std::move(identifier))
{
}

void VariableAccess::setScope(ance::Scope* scope)
{
	variable_ = scope->getVariable(identifier_);
}

ance::Type* VariableAccess::getType()
{
	return variable_->type();
}

ance::Value* VariableAccess::getValue()
{
	return value_;
}

void VariableAccess::build(
	llvm::LLVMContext& c,
	llvm::Module* m,
	CompileState* state,
	llvm::IRBuilder<>& ir,
	llvm::DIBuilder* di
)
{
	ance::Value* value = variable_->getValue(c, m, state, ir, di);
	value_->setValue(value);
}

VariableAccess::~VariableAccess() = default;