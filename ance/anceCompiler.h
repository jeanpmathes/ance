#pragma once
#include "Application.h"
#include <filesystem>
class anceCompiler
{
public:
	void Compile(Application& application, const std::filesystem::path& output_dir);
};
