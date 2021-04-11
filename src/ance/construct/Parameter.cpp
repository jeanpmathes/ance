#include "Parameter.h"

#include "ValueWrapper.h"

ance::Parameter::Parameter(ance::Type* type, std::string name) : type_(type), name_(name), wrapper_(new ValueWrapper(type)), argument_(nullptr)
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

ance::Value* ance::Parameter::get_value()
{
	return wrapper_;
}

void ance::Parameter::wrap(llvm::Argument* argument)
{
	argument_ = argument;
	argument->setName(name_);

	wrapper_->set_value(argument);
}

llvm::Argument* ance::Parameter::get_wrapped()
{
	return argument_;
}