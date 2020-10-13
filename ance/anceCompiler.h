#pragma once
#include "Application.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/DIBuilder.h"
#include <filesystem>
class anceCompiler
{
public:
	anceCompiler(Application& app);
	void Compile(const std::filesystem::path& output_dir);

private:
	void BuildApplication(llvm::Function* main);
	void LinkModule(std::filesystem::path& bc, std::filesystem::path& exe, std::filesystem::path& pdb);

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
};
