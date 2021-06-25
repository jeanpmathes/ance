#include "Function.h"

#include <utility>

ance::Function::Function(std::string fn_name, ance::Type* return_type, unsigned int l, unsigned int c) : name_(std::move(fn_name)), return_type_(return_type), line_(l), column_(c)
{

}

std::string ance::Function::getName() const
{
	return name_;
}

ance::Type* ance::Function::getReturnType() const
{
	return return_type_;
}

unsigned int ance::Function::getLine() const
{
	return line_;
}
