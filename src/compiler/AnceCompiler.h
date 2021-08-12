#ifndef ANCE_SRC_COMPILER_ANCECOMPILER_H_
#define ANCE_SRC_COMPILER_ANCECOMPILER_H_

#include <filesystem>

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Target/TargetMachine.h>

#include "compiler/Application.h"
#include "compiler/CompileContext.h"

class AnceCompiler
{
  public:
    explicit AnceCompiler(Application& app);

    void compile();
    void emitObject(const std::filesystem::path& out);

  private:
    void buildExit(llvm::FunctionType*& exit_type, llvm::Function*& exit);

    void buildStart(llvm::FunctionType* main_type,
                    llvm::Function*     main,
                    llvm::FunctionType* exit_type,
                    llvm::Function*     exit);

  private:
    Application&      application_;
    llvm::LLVMContext llvm_context_;
    llvm::IRBuilder<> ir_;

    llvm::TargetMachine* target_machine_{nullptr};

  private:
    llvm::Module*    module_;
    llvm::DIBuilder* di_;
    CompileContext*  context_;
};

#endif