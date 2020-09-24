#include "Application.h"

Application::Application()
{
}

void Application::PushStatement(const Statement& statement)
{
	statements.push_back(statement);
}

Statement& Application::PopStatement()
{
	Statement& statement = statements.front();
	statements.pop_front();
	return statement;
}