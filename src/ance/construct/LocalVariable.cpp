#include "LocalVariable.h"

#include <utility>

#include "LocalScope.h"
#include "WrappedNativeValue.h"
#include "CompileContext.h"

ance::LocalVariable::LocalVariable(
	ance::LocalScope* containing_scope,
	std::string identifier,
	ance::Type* type,
	ance::Value* value
)
	: Variable(containing_scope, std::move(identifier), type, false), initial_value_(value)
{
}

void ance::LocalVariable::build(CompileContext* context)
{
	assert(initial_value_);

	if (type()->storage() == InternalStorage::AS_POINTER)
	{
		native_value_ = context->ir()->CreateAlloca(type()->getContentType(*context->context()), nullptr);
		native_value_->setName(identifier());
	}

	setValue(initial_value_, context);
}

ance::Value* ance::LocalVariable::getValue(CompileContext*)
{
	return new WrappedNativeValue(type(), native_value_);
}

void ance::LocalVariable::setValue(ance::Value* value, CompileContext* context)
{
	assert(type() == value->getType() && "Assignment types have to match.");

	switch (type()->storage())
	{
		case InternalStorage::AS_TEMPORARY:
		{
			value->buildNativeValue(context);

			native_value_ = value->getNativeValue();
			native_value_->setName(identifier());
			break;
		}

		case InternalStorage::AS_POINTER:
		{
			value->buildContentValue(context);

			llvm::Value* stored = value->getContentValue();
			context->ir()->CreateStore(stored, native_value_);
			break;
		}
	}
}