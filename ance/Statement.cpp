#include "Statement.h"

Statement::Statement(unsigned int l, unsigned int c)
{
	line = l;
	column = c;
}

unsigned int Statement::getLine() const
{
	return line;
}

unsigned int Statement::getColumn() const
{
	return column;
}

Statement::~Statement()
{
}