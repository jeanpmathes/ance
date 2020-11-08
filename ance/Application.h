#ifndef APPLICATION_H
#define APPLICATION_H

#include <filesystem>
#include <map>

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/DIBuilder.h"

#include "Statement.h"
#include "Function.h"
#include "CompileState.h"

class Statement;
class CompileState;

namespace ance { class Function; }

class Application
{
public:
	Application(std::filesystem::path project_file, std::filesystem::path nccode_file);

	const std::string GetName() const;
	const std::filesystem::path GetProjectFile() const;
	const std::filesystem::path GetCodeFile() const;

	bool Validate();

	size_t FunctionCount() const;
	void AddFunctionName(std::string name);
	void AddAndEnterFunction(ance::Function* function);

	void PushStatementToCurrentFunction(Statement* statement);

	void BuildFunctionNames(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di);
	void BuildFunctions(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di);

	ance::Function* GetFunction(std::string identifier);

private:
	std::filesystem::path proj_file;
	std::filesystem::path code_file;

	std::map<std::string, ance::Function*> functions;
	ance::Function* current;
};

#endif