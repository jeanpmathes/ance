#include "Statement.h"

Statement::Statement(ance::Function* function, unsigned int l, unsigned int c) : function_(function)
{
	line = l;
	column = c;
}

ance::Function* Statement::get_containing_function() const
{
	return function_;
}

unsigned int Statement::getLine() const
{
	return line;
}

unsigned int Statement::getColumn() const
{
	return column;
}

Statement::~Statement() = default;