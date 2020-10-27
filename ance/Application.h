#pragma once
#include <list>
#include "Statement.h"
#include <filesystem>

class Application
{
public:
	Application(std::filesystem::path project_file, std::filesystem::path nccode_file);

	const std::string GetName() const;
	const std::filesystem::path GetProjectFile() const;
	const std::filesystem::path GetCodeFile() const;

	size_t StatementCount() const;
	void PushStatement(Statement* statement);
	Statement* PopStatement();

private:
	std::filesystem::path proj_file;
	std::filesystem::path code_file;
	std::list<Statement*> statements;
};
