#pragma once
#include <list>
#include "Statement.h"

class Application
{
public:
	Application();
	void PushStatement(const Statement& statement);
	Statement& PopStatement();

private:
	std::list<Statement> statements;
};
