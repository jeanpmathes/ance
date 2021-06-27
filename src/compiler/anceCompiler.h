#ifndef ANCE_SRC_COMPILER_ANCECOMPILER_H_
#define ANCE_SRC_COMPILER_ANCECOMPILER_H_

#include <filesystem>

#include "Application.h"
#include "CompileState.h"

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/DIBuilder.h"

class anceCompiler
{
	public:
		explicit anceCompiler(Application& app);

		void compile(const std::filesystem::path& output_dir);

	private:
		void buildExit(llvm::FunctionType*& exit_type, llvm::Function*& exit);

		void buildStart(
			llvm::FunctionType* main_type,
			llvm::Function* main,
			llvm::FunctionType* exit_type,
			llvm::Function* exit
		);

		void linkModule(std::filesystem::path& bc, std::filesystem::path& exe);

	private:
		Application& application_;
		llvm::LLVMContext context_;
		llvm::IRBuilder<> ir_;

	private:
		llvm::Module* module_;

		llvm::DIBuilder* di_;
		llvm::DIFile* proj_file_;
		llvm::DICompileUnit* unit_;
		llvm::DIFile* code_file_;

		CompileState* state_;
};

#endif