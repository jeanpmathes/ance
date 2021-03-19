#ifndef APPLICATION_H
#define APPLICATION_H

#include <filesystem>

#include "Scope.h"

class Statement;
class CompileState;

namespace ance {
	class Scope;
	class Function;
}

class Application
{
public:
	Application(std::filesystem::path project_file, std::filesystem::path nccode_file);
	void set_pointer_size(unsigned size);

	const std::string GetName() const;
	const std::filesystem::path GetProjectFile() const;
	const std::filesystem::path GetCodeFile() const;

	unsigned get_bitness();

	bool Validate();

	ance::GlobalScope* global_scope();

private:
	std::filesystem::path proj_file;
	std::filesystem::path code_file;

	ance::GlobalScope* global_scope_;

	unsigned pointer_size_;
};

#endif