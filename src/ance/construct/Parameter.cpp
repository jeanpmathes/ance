#include "Parameter.h"

#include <utility>

#include "Type.h"

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
	argument_ = argument;

	switch (type_->storage())
	{
		case InternalStorage::AS_TEMPORARY:
		{
			argument_->setName(name_);
			break;
		}
		case InternalStorage::AS_POINTER:
		{
			argument_->setName(name_ + ".content");
			break;
		}
	}
}

void ance::Parameter::build(
	llvm::LLVMContext&,
	llvm::Module*,
	CompileState*,
	llvm::IRBuilder<>&,
	llvm::DIBuilder*
)
{
}

llvm::Value* ance::Parameter::getNativeValue()
{
	assert(type_->storage() == InternalStorage::AS_TEMPORARY && "Native argument has to be native value.");
	return argument_;
}

llvm::Value* ance::Parameter::getContentValue(
	llvm::LLVMContext&,
	llvm::Module*,
	CompileState*,
	llvm::IRBuilder<>&,
	llvm::DIBuilder*
)
{
	assert(type_->storage() == InternalStorage::AS_POINTER && "Native argument has to be content value.");
	return argument_;
}
