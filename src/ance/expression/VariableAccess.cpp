#include "VariableAccess.h"

#include <utility>

#include "ExpressionBackedValue.h"
#include "Value.h"
#include "Scope.h"

VariableAccess::VariableAccess(std::string identifier)
	: identifier_(std::move(identifier)), value_(new ance::ExpressionBackedValue(this))
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

llvm::Value* VariableAccess::build(
	llvm::LLVMContext& c,
	llvm::Module* m,
	CompileState* state,
	llvm::IRBuilder<>& ir,
	llvm::DIBuilder* di
)
{
	return variable_->getValue(c, m, state, ir, di);
}

VariableAccess::~VariableAccess() = default;