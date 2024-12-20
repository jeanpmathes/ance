#ifndef ANCE_SRC_COMPILER_ANCECOMPILER_H_
#define ANCE_SRC_COMPILER_ANCECOMPILER_H_

#include <filesystem>

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Target/TargetMachine.h>

#include "TargetDescriptor.h"

#include "compiler/Runtime.h"
#include "compiler/native/NativeBuild.h"
#include "lang/construct/Function.h"
#include "lang/utility/Owners.h"

class Unit;
class SourceTree;

/**
 * Represents the compile step, which transforms a unit into a llvm module.
 */
class AnceCompiler
{
  public:
    /**
     * Create a new compiler for a unit.
     * @param tree The source tree.
     * @param target_descriptor The target descriptor.
     */
    AnceCompiler(SourceTree& tree, TargetDescriptor target_descriptor);

    /**
     * Compile the application, emitting an object file and potentially an IR file.
     * @param ilr The path at which to emit the IR file.
     * @param obj The path at which to emit the object file.
     * @param validation_logger The logger for validation messages.
     */
    void compile(std::filesystem::path const& ilr,
                 std::filesystem::path const& obj,
                 ValidationLogger&            validation_logger);

  private:
    llvm::Function* buildInit();
    llvm::Function* buildFinit();
    void            buildStart(lang::ResolvingHandle<lang::Function> main, llvm::Function* init, llvm::Function* finit);
    void            buildLibStart(llvm::Function* init, llvm::Function* finit);
    static std::string getInternalFunctionName(std::string const& name);

  public:
    static constexpr char const* WIN_EXE_MAIN_NAME =
        "main";// As the console subsystem is used, WinMain would be incorrect.

    static constexpr std::array<char const*, 1> BUILTIN_NAMES = {WIN_EXE_MAIN_NAME};

  private:
    static constexpr char const* INTERNAL_FUNCTION_SUFFIX = "$lang";

    llvm::LLVMContext llvm_context_;
    llvm::Module      module_;
    llvm::IRBuilder<> ir_;
    llvm::DIBuilder   di_;

    Unit&               unit_;
    TargetDescriptor    target_descriptor_;
    Runtime           runtime_;
    NativeBuild         native_build_;

    llvm::TargetMachine* target_machine_ {nullptr};
};

#endif
