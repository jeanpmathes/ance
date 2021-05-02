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

		// native: AllocConsole

	public:
		llvm::Value* buildnativecall_AllocConsole() const;

	private:
		llvm::FunctionType* alloc_console_type_;
		llvm::Function* alloc_console_;

		// native: AttachConsole

	public:
		llvm::Value* buildnativecall_AttachConsole(int32_t pid) const;

	private:
		llvm::FunctionType* attach_console_type_;
		llvm::Function* attach_console_;

		// native: FreeConsole

	public:
		llvm::Value* buildnativecall_FreeConsole() const;

	private:
		llvm::FunctionType* free_console_type_;
		llvm::Function* free_console_;

		// native: GetStdHandle

	public:
		llvm::Value* buildnativecall_GetStdHandle(int32_t nStdHandle) const;

	private:
		llvm::FunctionType* get_std_handle_type_;
		llvm::Function* get_std_handle_;

		// native: WriteFile (Kernel32)

	public:
		llvm::Value* buildnativecall_WriteFile(
			llvm::Value* hFile,
			llvm::Value* lpBuffer,
			llvm::Value* nNumberOfBytesToWrite,
			llvm::Value* lpNumberOfBytesWritten,
			llvm::Value* lpOverlapped
		) const;

	private:
		llvm::FunctionType* write_file_type_;
		llvm::Function* write_file_;

		// native: ExitProcess (Kernel32)

	public:
		void buildnativecall_ExitProcess(llvm::Value* uExitCode) const;

	private:
		llvm::FunctionType* exit_process_type_;
		llvm::Function* exit_process_;
};

#endif