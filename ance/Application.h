#pragma once
#include <list>
#include "Statement.h"
#include <filesystem>

class Application
{
public:
	Application(std::filesystem::path project_file, std::filesystem::path nccode_file);

	const std::string GetName();
	const std::filesystem::path GetProjectFile();
	const std::filesystem::path GetCodeFile();

	size_t StatementCount();
	void PushStatement(Statement* statement);
	Statement* PopStatement();

private:
	std::filesystem::path proj_file;
	std::filesystem::path code_file;
	std::list<Statement*> statements;
};
