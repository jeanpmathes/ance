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

class Unit;

/**
 * Represents the compile step, which transforms a unit into a llvm module.
 */
class AnceCompiler
{
  public:
    /**
     * Create a new compiler for a unit.
     * @param tree The source tree.
     * @param triple The target triple.
     */
    AnceCompiler(SourceTree& tree, llvm::Triple const& triple);

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
    llvm::Function* buildFinit();
    void            buildStart(lang::ResolvingHandle<lang::Function> main, llvm::Function* init, llvm::Function* finit);
    void            buildLibStart(llvm::Function* init, llvm::Function* finit);
    static std::string getInternalFunctionName(std::string const& name);

  public:
    static constexpr char const* WIN_EXE_MAIN_NAME =
        "main";// As the console subsystem is used, WinMain would be incorrect.
    static constexpr char const* WIN_DLL_MAIN_NAME = "DllMain";

    static constexpr std::array<char const*, 2> BUILTIN_NAMES = {WIN_EXE_MAIN_NAME, WIN_DLL_MAIN_NAME};

  private:
    static constexpr char const* INTERNAL_FUNCTION_SUFFIX = "$lang";

    Unit&             unit_;
    llvm::Triple      triple_;
    llvm::LLVMContext llvm_context_;
    llvm::Module      module_;
    llvm::IRBuilder<> ir_;
    llvm::DIBuilder   di_;
    Runtime           runtime_;
    CompileContext    context_;

    llvm::TargetMachine* target_machine_ {nullptr};
};

#endif
