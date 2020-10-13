#include "Application.h"

Application::Application(const std::string& n)
{
	name = std::string(n);
}

const std::string Application::GetName()
{
	return name;
}

size_t Application::StatementCount()
{
	return statements.size();
}

void Application::PushStatement(Statement* statement)
{
	statements.push_back(statement);
}

Statement* Application::PopStatement()
{
	Statement* statement = statements.front();
	statements.pop_front();
	return statement;
}