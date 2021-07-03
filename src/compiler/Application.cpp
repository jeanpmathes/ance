#include "Application.h"

#include <iostream>

#include "Element.h"

#include "GlobalScope.h"

#include "HalfType.h"
#include "SingleType.h"
#include "DoubleType.h"
#include "QuadType.h"

#include "VoidType.h"
#include "SizeType.h"
#include "UnsignedIntegerPointerType.h"

Application::Application(data::File& project)
	: project_(project), global_scope_(new ance::GlobalScope())
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
	return project_.root()["name"].asString();
}

std::filesystem::path Application::getProjectFile() const
{
	return project_.path();
}

std::filesystem::path Application::getSourceFile() const
{
	for (const auto* src : project_.root()["src"])
	{
		std::filesystem::path path_to_src(src->asString());
		std::filesystem::path path_to_project = getProjectFile();

		return path_to_project.replace_filename(path_to_src);
	}

	return std::filesystem::path();
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

	if (!global_scope_->hasFunction("exit"))
	{
		std::cout << "No exit function was found!" << std::endl;

		valid = false;
	}

	return valid;
}

ance::GlobalScope* Application::globalScope()
{
	return global_scope_;
}
