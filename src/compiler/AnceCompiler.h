#ifndef ANCE_SRC_COMPILER_ANCECOMPILER_H_
#define ANCE_SRC_COMPILER_ANCECOMPILER_H_

#include <filesystem>

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Target/TargetMachine.h>

#include "compiler/CompileContext.h"
#include "compiler/Runtime.h"
#include "lang/construct/Function.h"
#include "lang/utility/Owners.h"

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
     * @param tree The source tree.
     */
    AnceCompiler(Application& app, SourceTree& tree);

    /**
     * Compile the application.
     * @param out Path to emit the llvm IR at.
     */
    void compile(std::filesystem::path const& out);
    /**
     * Emit object files.
     * @param out The path of the object files.
     */
    void emitObject(std::filesystem::path const& out);

  private:
    llvm::Function* buildInit();
    llvm::Function* buildExit();
    void            buildStart(lang::ResolvingHandle<lang::Function> main, llvm::Function* init, llvm::Function* exit);
    static std::string getInternalFunctionName(std::string const& name);

  private:
    static constexpr char const* INTERNAL_FUNCTION_SUFFIX = "$lang";

    Application&      application_;
    llvm::LLVMContext llvm_context_;
    llvm::Module      module_;
    llvm::IRBuilder<> ir_;
    llvm::DIBuilder   di_;
    Runtime           runtime_;
    CompileContext    context_;

    llvm::TargetMachine* target_machine_ {nullptr};
};

#endif
