#ifndef ANCE_SRC_COMPILER_ANCECOMPILER_H_
#define ANCE_SRC_COMPILER_ANCECOMPILER_H_

#include <filesystem>

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Target/TargetMachine.h>

#include "compiler/Application.h"
#include "compiler/CompileContext.h"

/**
 * Represents the compile step, which transforms an application into a llvm module.
 */
class AnceCompiler
{
  public:
    /**
     * Create a new compiler for an application.
     * @param app The application.
     */
    explicit AnceCompiler(Application& app);

    /**
     * Compile the application.
     * @param out Path to emit the llvm IR at.
     */
    void compile(const std::filesystem::path& out);
    /**
     * Emit object files.
     * @param out The path of the object files.
     */
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

    llvm::TargetMachine* target_machine_ {nullptr};

  private:
    llvm::Module*    module_;
    llvm::DIBuilder* di_;
    CompileContext*  context_;
};

#endif