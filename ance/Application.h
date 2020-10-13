#pragma once
#include <list>
#include "Statement.h"

class Application
{
public:
	Application(const std::string& n);

	const std::string GetName();

	size_t StatementCount();
	void PushStatement(Statement* statement);
	Statement* PopStatement();

private:
	std::string name;
	std::list<Statement*> statements;
};
