#ifndef COMPILESTATE_H
#define COMPILESTATE_H

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/DIBuilder.h"

#include "Application.h"

class Application;

class CompileState
{
public:
	CompileState(llvm::LLVMContext* c, llvm::Module* m, llvm::IRBuilder<>* ir, llvm::DIBuilder* di);

private:
	llvm::LLVMContext* context;
	llvm::Module* module;
	llvm::IRBuilder<>* ir_builder;
	llvm::DIBuilder* di_builder;

public:
	Application* application;
	llvm::DICompileUnit* unit;
	llvm::DIFile* code_file;
	llvm::DIBasicType* ui32;

	// native: AllocConsole

public:
	llvm::Value* buildnativecall_AllocConsole() const;

private:
	llvm::FunctionType* allocConsole_type;
	llvm::Function* allocConsole;

	// native: AttachConsole

public:
	llvm::Value* buildnativecall_AttachConsole(int32_t pid) const;

private:
	llvm::FunctionType* attachConsole_type;
	llvm::Function* attachConsole;

	// native: FreeConsole

public:
	llvm::Value* buildnativecall_FreeConsole() const;

private:
	llvm::FunctionType* freeConsole_type;
	llvm::Function* freeConsole;

	// native: GetStdHandle

public:
	llvm::Value* buildnativecall_GetStdHandle(int32_t nStdHandle) const;

private:
	llvm::FunctionType* getStdHandle_type;
	llvm::Function* getStdHandle;

	// native: WriteFile (Kernel32)

public:
	llvm::Value* buildnativecall_WriteFile(llvm::Value* hFile, llvm::Value* lpBuffer, llvm::Value* nNumberOfBytesToWrite, llvm::Value* lpNumberOfBytesWritten, llvm::Value* lpOverlapped) const;

private:
	llvm::FunctionType* writeFile_type;
	llvm::Function* writeFile;

	// native: ExitProcess (Kernel32)

public:
	void buildnativecall_ExitProcess(llvm::Value* uExitCode) const;

private:
	llvm::FunctionType* exitProcess_type;
	llvm::Function* exitProcess;
};
#endif