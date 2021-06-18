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

	if (type()->storage() == InternalStorage::AS_POINTER)
	{
		native_value_ = ir.CreateAlloca(type()->getContentType(c), nullptr);
		native_value_->setName(identifier());
	}

	setValue(initial_value_, c, m, state, ir, di);
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

	switch (type()->storage())
	{
		case InternalStorage::AS_TEMPORARY:
		{
			value->buildNativeValue(c, m, state, ir, di);

			native_value_ = value->getNativeValue();
			native_value_->setName(identifier());
			break;
		}

		case InternalStorage::AS_POINTER:
		{
			value->buildContentValue(c, m, state, ir, di);

			llvm::Value* stored = value->getContentValue();
			ir.CreateStore(stored, native_value_);
			break;
		}
	}
}