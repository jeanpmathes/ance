#include "Statement.h"

Statement::Statement(ance::Function* function, unsigned int l, unsigned int c)
	: function_(function), line_(l), column_(c)
{
}

ance::Function* Statement::getContainingFunction() const
{
	return function_;
}

unsigned int Statement::getLine() const
{
	return line_;
}

unsigned int Statement::getColumn() const
{
	return column_;
}

Statement::~Statement() = default;