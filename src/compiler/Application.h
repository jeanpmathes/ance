#ifndef ANCE_SRC_COMPILER_APPLICATION_H_
#define ANCE_SRC_COMPILER_APPLICATION_H_

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
	void setPointerSize(unsigned size);

	[[nodiscard]] const std::string getName() const;
	[[nodiscard]] const std::filesystem::path getProjectFile() const;
	[[nodiscard]] const std::filesystem::path getCodeFile() const;

	unsigned getBitness();

	bool validate();

	ance::GlobalScope* globalScope();

private:
	std::filesystem::path proj_file_;
	std::filesystem::path code_file_;

	ance::GlobalScope* global_scope_;

	unsigned pointer_size_;
};

#endif