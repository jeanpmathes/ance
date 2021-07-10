#ifndef ANCE_SRC_COMPILER_COMPILECONTEXT_H_
#define ANCE_SRC_COMPILER_COMPILECONTEXT_H_

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/DIBuilder.h>

#include "Application.h"
#include "Runtime.h"

class Application;

class CompileContext
{
	public:
		CompileContext(llvm::LLVMContext* c, llvm::Module* m, llvm::IRBuilder<>* ir, llvm::DIBuilder* di);

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
};

#endif