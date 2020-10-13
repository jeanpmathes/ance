#include "Statement.h"

Statement::Statement(unsigned int l, unsigned int c)
{
	line = l;
	column = c;
}

unsigned int Statement::getLine()
{
	return line;
}

unsigned int Statement::getColumn()
{
	return column;
}

Statement::~Statement()
{
}