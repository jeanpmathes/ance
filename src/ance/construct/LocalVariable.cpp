#include "LocalVariable.h"

#include <utility>

#include "LocalScope.h"
#include "Value.h"

ance::LocalVariable::LocalVariable(
	ance::LocalScope* containing_scope,
	std::string identifier,
	ance::Type* type,
	ance::Value* value
)
	: Variable(containing_scope, std::move(identifier), type, false), value_(value)
{
}

void ance::LocalVariable::build(
	llvm::LLVMContext& c,
	llvm::Module* m,
	CompileState* state,
	llvm::IRBuilder<>& ir,
	llvm::DIBuilder* di
)
{
	assert(value_);
	assert(type() == value_->getType());

	value_->build(c, m, state, ir, di);
	native_value_ = value_->getNativeValue();
	native_value_->setName(identifier());
}

llvm::Value* ance::LocalVariable::getValue(
	llvm::LLVMContext&,
	llvm::Module*,
	CompileState*,
	llvm::IRBuilder<>&,
	llvm::DIBuilder*
)
{
	return native_value_;
}

void ance::LocalVariable::setValue(
	llvm::Value* value,
	llvm::LLVMContext&,
	llvm::Module*,
	CompileState*,
	llvm::IRBuilder<>&,
	llvm::DIBuilder*
)
{
	native_value_ = value;
	native_value_->setName(identifier());
}