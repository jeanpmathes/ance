#include "Function.h"

#include <utility>

ance::Function::Function(std::string function_name, ance::Type* return_type, unsigned int line, unsigned int column) : name_(std::move(function_name)), return_type_(return_type), line_(line), column_(column)
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
