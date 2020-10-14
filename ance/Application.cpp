#include "Application.h"

Application::Application(std::filesystem::path project_file, std::filesystem::path nccode_file) : proj_file(project_file), code_file(nccode_file)
{
}

const std::string Application::GetName()
{
	return proj_file.stem().string();
}

const std::filesystem::path Application::GetProjectFile()
{
	return std::filesystem::path(proj_file);
}

const std::filesystem::path Application::GetCodeFile()
{
	return std::filesystem::path(code_file);
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