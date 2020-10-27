#pragma once
#include "Application.h"
#include "CompileState.h"

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/DIBuilder.h"

#include <filesystem>
class anceCompiler
{
public:
	anceCompiler(Application& app);
	void Compile(const std::filesystem::path& output_dir);

private:
	void SetupGlobals();
	void BuildMain(llvm::DIBasicType* ui32, llvm::FunctionType*& main_type, llvm::Function*& main);
	void BuildApplication(llvm::Function* main);
	void BuildExit(llvm::FunctionType*& exit_type, llvm::Function*& exit);
	void BuildStart(llvm::FunctionType* main_type, llvm::Function* main, llvm::FunctionType* exit_type, llvm::Function* exit);
	void LinkModule(std::filesystem::path& bc, std::filesystem::path& exe);

private:
	Application& application;
	llvm::LLVMContext context;
	llvm::IRBuilder<> ir;

private:
	llvm::Module* module;

	llvm::DIBuilder* di;
	llvm::DIFile* proj_file;
	llvm::DICompileUnit* unit;
	llvm::DIFile* code_file;

	CompileState* state;
};
