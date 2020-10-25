#pragma once
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/DIBuilder.h"
class CompileState
{
public:
	CompileState(llvm::LLVMContext* c, llvm::Module* m, llvm::IRBuilder<>* ir, llvm::DIBuilder* di);

private:
	llvm::LLVMContext* context;
	llvm::Module* module;
	llvm::IRBuilder<>* ir_builder;
	llvm::DIBuilder* di_builder;

	// native: AllocConsole

public:
	llvm::Value* buildnativecall_AllocConsole();

private:
	llvm::FunctionType* allocConsole_type;
	llvm::Function* allocConsole;

	// native: AttachConsole

public:
	llvm::Value* buildnativecall_AttachConsole(int32_t pid);

private:
	llvm::FunctionType* attachConsole_type;
	llvm::Function* attachConsole;

	// native: FreeConsole

public:
	llvm::Value* buildnativecall_FreeConsole();

private:
	llvm::FunctionType* freeConsole_type;
	llvm::Function* freeConsole;

	// native: GetStdHandle

public:
	llvm::Value* buildnativecall_GetStdHandle(int32_t nStdHandle);

private:
	llvm::FunctionType* getStdHandle_type;
	llvm::Function* getStdHandle;

	// native: WriteFile (Kernel32)

public:
	llvm::Value* buildnativecall_WriteFile(llvm::Value* hFile, llvm::Value* lpBuffer, llvm::Value* nNumberOfBytesToWrite, llvm::Value* lpNumberOfBytesWritten, llvm::Value* lpOverlapped);

private:
	llvm::FunctionType* writeFile_type;
	llvm::Function* writeFile;

	// native: ExitProcess (Kernel32)

public:
	void buildnativecall_ExitProcess(llvm::Value* uExitCode);

private:
	llvm::FunctionType* exitProcess_type;
	llvm::Function* exitProcess;
};
