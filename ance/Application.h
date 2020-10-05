#pragma once
#include <list>
#include "Statement.h"

class Application
{
public:
	Application();
	size_t StatementCount();
	void PushStatement(Statement* statement);
	Statement* PopStatement();

private:
	std::list<Statement*> statements;
};
