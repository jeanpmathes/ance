#include "Application.h"

#include <iostream>
#include <utility>

#include "GlobalScope.h"

Application::Application(std::filesystem::path project_file, std::filesystem::path nccode_file)
    : proj_file_(std::move(project_file)), code_file_(std::move(nccode_file)), global_scope_(new ance::GlobalScope())
{
}

void Application::setPointerSize(unsigned size)
{
	pointer_size_ = size;
}

std::string Application::getName() const
{
	return proj_file_.stem().string();
}

std::filesystem::path Application::getProjectFile() const
{
	return std::filesystem::path(proj_file_);
}

std::filesystem::path Application::getCodeFile() const
{
	return std::filesystem::path(code_file_);
}

unsigned Application::getBitness()
{
	return pointer_size_ * 8;
}

bool Application::validate()
{
	bool valid = global_scope_->validate();

	if (!global_scope_->hasFunction("main"))
	{
		std::cout << "No main function was found!" << std::endl;

		valid = false;
	}

	return valid;
}

ance::GlobalScope* Application::globalScope()
{
	return global_scope_;
}