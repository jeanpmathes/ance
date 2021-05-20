#include "VariableAssignable.h"

VariableAssignable::VariableAssignable(std::string variable_identifier) : variable_identifier_(std::move(variable_identifier))
{

}

void VariableAssignable::setScope(ance::Scope* scope)
{
	scope_ = scope;
}

void VariableAssignable::assign(
	ance::Value* value,
	llvm::LLVMContext& c,
	llvm::Module* m,
	CompileState* state,
	llvm::IRBuilder<>& ir,
	llvm::DIBuilder* di
)
{
	ance::Variable* variable = scope_->getVariable(variable_identifier_);
	assert(variable->type() == value->getType() && "Assignment types have to match.");

	value->build(c, m, state, ir, di);
	variable->setValue(value->getNativeValue(), c, m, state, ir, di);
}
