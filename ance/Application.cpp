#include "Application.h"

#include <iostream>

Application::Application(std::filesystem::path project_file, std::filesystem::path nccode_file) : proj_file(project_file), code_file(nccode_file), current(nullptr)
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
	bool valid = true;

	for (auto const& [key, val] : functions)
	{
		if (val == nullptr)
		{
			std::cout << "A function is used but not defined: " << key << std::endl;

			valid = false;
		}
	}

	if (functions.find("main") == functions.end())
	{
		std::cout << "No main function was found!" << std::endl;

		valid = false;
	}

	return valid;
}

size_t Application::FunctionCount() const
{
	return functions.size();
}

void Application::AddFunctionName(std::string name)
{
	if (functions.find(name) == functions.end()) functions[name] = nullptr;
}

void Application::AddAndEnterFunction(ance::Function* function)
{
	functions[function->GetName()] = function;
	current = function;
}

void Application::PushStatementToCurrentFunction(Statement* statement)
{
	current->push_statement(statement);
}

void Application::BuildFunctionNames(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	for (auto const& [key, val] : functions)
	{
		val->BuildName(c, m, state, ir, di);
	}
}

void Application::BuildFunctions(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	for (auto const& [key, val] : functions)
	{
		val->Build(c, m, state, ir, di);
	}
}

ance::Function* Application::GetFunction(std::string identifier)
{
	return functions.at(identifier);
}