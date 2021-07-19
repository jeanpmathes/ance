#ifndef ANCE_SRC_COMPILER_ANCECOMPILER_H_
#define ANCE_SRC_COMPILER_ANCECOMPILER_H_

#include <filesystem>

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>

#include "compiler/Application.h"
#include "compiler/CompileContext.h"

class AnceCompiler
{
  public:
    explicit AnceCompiler(Application& app);

    void compile(const std::filesystem::path& bc);

  private:
    void buildExit(llvm::FunctionType*& exit_type, llvm::Function*& exit);

    void buildStart(
        llvm::FunctionType* main_type,
        llvm::Function*     main,
        llvm::FunctionType* exit_type,
        llvm::Function*     exit);

  private:
    Application&      application_;
    llvm::LLVMContext llvm_context_;
    llvm::IRBuilder<> ir_;

  private:
    llvm::Module*    module_;
    llvm::DIBuilder* di_;
    CompileContext*  context_;
};

#endif