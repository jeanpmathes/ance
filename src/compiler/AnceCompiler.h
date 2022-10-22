#ifndef ANCE_SRC_COMPILER_ANCECOMPILER_H_
#define ANCE_SRC_COMPILER_ANCECOMPILER_H_

#include <filesystem>

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Target/TargetMachine.h>

#include "lang/construct/Function.h"
#include "compiler/CompileContext.h"
#include "compiler/Runtime.h"

class Application;

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
    llvm::Function* buildInit();
    llvm::Function* buildExit();
    void            buildStart(lang::ResolvingHandle<lang::Function> main, llvm::Function* init, llvm::Function* exit);
    static std::string getInternalFunctionName(const std::string& name);

  private:
    static constexpr const char* INTERNAL_FUNCTION_SUFFIX = "$lang";

    Application&      application_;
    llvm::LLVMContext llvm_context_;
    llvm::Module      module_;
    llvm::IRBuilder<> ir_;
    llvm::DIBuilder   di_;

    llvm::TargetMachine*            target_machine_ {nullptr};
    std::unique_ptr<CompileContext> context_ {};
    std::unique_ptr<Runtime>        runtime_ {};
};

#endif
