#include "Parameter.h"

#include "WrappedNativeValue.h"

ance::Parameter::Parameter(ance::Type* type, std::string name) : type_(type), name_(name), wrapper_(new WrappedNativeValue(type)), argument_(nullptr)
{
}

ance::Type* ance::Parameter::type()
{
	return type_;
}

std::string ance::Parameter::name()
{
	return name_;
}

ance::Value* ance::Parameter::getValue()
{
	return wrapper_;
}

void ance::Parameter::wrap(llvm::Argument* argument)
{
	argument_ = argument;
	argument->setName(name_);

    wrapper_->setValue(argument);
}

llvm::Argument* ance::Parameter::getWrapped()
{
	return argument_;
}