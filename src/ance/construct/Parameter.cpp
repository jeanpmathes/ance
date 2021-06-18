#include "Parameter.h"

#include <utility>

#include "Type.h"
#include "Values.h"

ance::Parameter::Parameter(ance::Type* type, std::string name)
	: type_(type), name_(std::move(name))
{
}

ance::Type* ance::Parameter::getType()
{
	return type_;
}

std::string ance::Parameter::name()
{
	return name_;
}

void ance::Parameter::wrap(llvm::Argument* argument)
{
	switch (type_->storage())
	{
		case InternalStorage::AS_TEMPORARY:
		{
			native_value_ = argument;
			native_value_->setName(name_);
			break;
		}
		case InternalStorage::AS_POINTER:
		{
			content_value_ = argument;
			content_value_->setName(name_ + ".content");
			break;
		}
	}
}

void ance::Parameter::buildNativeValue(
	llvm::LLVMContext& c,
	llvm::Module* m,
	CompileState* state,
	llvm::IRBuilder<>& ir,
	llvm::DIBuilder* di
)
{
	if (!native_value_)
	{
		native_value_ = ance::Values::contentToNative(getType(), content_value_, c, m, state, ir, di);
	}
}

void ance::Parameter::buildContentValue(
	llvm::LLVMContext& c,
	llvm::Module* m,
	CompileState* state,
	llvm::IRBuilder<>& ir,
	llvm::DIBuilder* di
)
{
	if (!content_value_)
	{
		content_value_ = ance::Values::nativeToContent(getType(), native_value_, c, m, state, ir, di);
	}
}

llvm::Value* ance::Parameter::getNativeValue()
{
	return native_value_;
}

llvm::Value* ance::Parameter::getContentValue()
{
	return content_value_;
}
