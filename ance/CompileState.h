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

	// native: ExitProcess (Kernel32)

public:
	void buildnativecall_ExitProcess(llvm::Argument* exit_code);

private:
	llvm::FunctionType* exitProcess_type;
	llvm::Function* exitProcess;
};
