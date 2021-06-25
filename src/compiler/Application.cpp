#include "Application.h"

#include <iostream>
#include <utility>

#include "GlobalScope.h"

#include "HalfType.h"
#include "SingleType.h"
#include "DoubleType.h"
#include "QuadType.h"

#include "VoidType.h"
#include "SizeType.h"
#include "UnsignedIntegerPointerType.h"

Application::Application(std::filesystem::path project_file, std::filesystem::path nccode_file)
	: proj_file_(std::move(project_file)), code_file_(std::move(nccode_file)), global_scope_(new ance::GlobalScope())
{
	// Register keyword types

	global_scope_->registerType(ance::HalfType::get());
	global_scope_->registerType(ance::SingleType::get());
	global_scope_->registerType(ance::DoubleType::get());
	global_scope_->registerType(ance::QuadType::get());

	global_scope_->registerType(ance::VoidType::get());
	global_scope_->registerType(ance::SizeType::get());
	global_scope_->registerType(ance::UnsignedIntegerPointerType::get());
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

unsigned Application::getBitness() const
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
