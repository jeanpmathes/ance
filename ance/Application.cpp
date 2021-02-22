#include "Application.h"

#include <iostream>

#include "GlobalScope.h"

Application::Application(std::filesystem::path project_file, std::filesystem::path nccode_file) : proj_file(project_file), code_file(nccode_file), global_scope_(new ance::GlobalScope())
{
}

const std::string Application::GetName() const
{
	return proj_file.stem().string();
}

const std::filesystem::path Application::GetProjectFile() const
{
	return std::filesystem::path(proj_file);
}

const std::filesystem::path Application::GetCodeFile() const
{
	return std::filesystem::path(code_file);
}

bool Application::Validate()
{
	bool valid = global_scope_->validate();

	if (!global_scope_->HasFunction("main"))
	{
		std::cout << "No main function was found!" << std::endl;

		valid = false;
	}

	return valid;
}

ance::GlobalScope* Application::global_scope()
{
	return global_scope_;
}