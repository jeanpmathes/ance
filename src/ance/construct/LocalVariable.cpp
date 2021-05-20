#include "LocalVariable.h"

#include <utility>

#include "LocalScope.h"
#include "WrappedNativeValue.h"

ance::LocalVariable::LocalVariable(
	ance::LocalScope* containing_scope,
	std::string identifier,
	ance::Type* type,
	ance::Value* value
)
	: Variable(containing_scope, std::move(identifier), type, false), initial_value_(value)
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
	assert(initial_value_);
	assert(type() == initial_value_->getType());

	initial_value_->build(c, m, state, ir, di);
	native_value_ = initial_value_->getNativeValue();
	native_value_->setName(identifier());
}

ance::Value* ance::LocalVariable::getValue(
	llvm::LLVMContext&,
	llvm::Module*,
	CompileState*,
	llvm::IRBuilder<>&,
	llvm::DIBuilder*
)
{
	return new WrappedNativeValue(type(), native_value_);
}

void ance::LocalVariable::setValue(
	ance::Value* value,
	llvm::LLVMContext& c,
	llvm::Module* m,
	CompileState* state,
	llvm::IRBuilder<>& ir,
	llvm::DIBuilder* di
)
{
	assert(type() == value->getType() && "Assignment types have to match.");

	value->build(c, m, state, ir, di);

	switch (type()->storage())
	{
		case InternalStorage::AS_TEMPORARY:
		{
			native_value_ = value->getNativeValue();
			native_value_->setName(identifier());
			break;
		}

		case InternalStorage::AS_POINTER:
		{
			llvm::Value* stored = value->getContentValue(c, m, state, ir, di);
			ir.CreateStore(native_value_, stored);
			break;
		}
	}
}