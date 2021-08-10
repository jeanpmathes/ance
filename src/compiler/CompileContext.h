#ifndef ANCE_SRC_COMPILER_COMPILECONTEXT_H_
#define ANCE_SRC_COMPILER_COMPILECONTEXT_H_

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>

#include "compiler/Application.h"
#include "compiler/Runtime.h"

class Application;

class CompileContext
{
  public:
    CompileContext(Application*         app,
                   Runtime*             runtime,
                   llvm::LLVMContext*   c,
                   llvm::Module*        m,
                   llvm::IRBuilder<>*   ir,
                   llvm::DIBuilder*     di,
                   llvm::DICompileUnit* unit,
                   llvm::DIFile*        src_file);

    Application* application();

    Runtime* runtime();

    llvm::LLVMContext* llvmContext();

    llvm::Module* module();

    llvm::IRBuilder<>* ir();

    llvm::DIBuilder* di();

    llvm::DICompileUnit* unit();

    llvm::DIFile* sourceFile();

  private:
    Application*         application_;
    Runtime*             runtime_;
    llvm::LLVMContext*   context_;
    llvm::Module*        module_;
    llvm::IRBuilder<>*   ir_builder_;
    llvm::DIBuilder*     di_builder_;
    llvm::DICompileUnit* unit_;
    llvm::DIFile*        src_file_;
};

#endif