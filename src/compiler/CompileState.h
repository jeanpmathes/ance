#ifndef ANCE_SRC_COMPILER_COMPILESTATE_H_
#define ANCE_SRC_COMPILER_COMPILESTATE_H_

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/DIBuilder.h>

#include "Application.h"
#include "Runtime.h"

class Application;

class CompileState
{
	public:
		CompileState(llvm::LLVMContext* c, llvm::Module* m, llvm::IRBuilder<>* ir, llvm::DIBuilder* di);

	private:
		llvm::LLVMContext* context_;
		llvm::Module* module_;
		llvm::IRBuilder<>* ir_builder_;
		llvm::DIBuilder* di_builder_;

	public:
		Application* application_;
		Runtime* runtime_;
		llvm::DICompileUnit* unit_{nullptr};
		llvm::DIFile* code_file_{nullptr};
		llvm::DIBasicType* ui_32_{nullptr};

		// native: ExitProcess (Kernel32)

	public:
		void buildnativecall_ExitProcess(llvm::Value* uExitCode) const;

	private:
		llvm::FunctionType* exit_process_type_;
		llvm::Function* exit_process_;
};

#endif