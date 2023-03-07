#ifndef ANCE_SRC_COMPILER_COMPILECONTEXT_H_
#define ANCE_SRC_COMPILER_COMPILECONTEXT_H_

#include <filesystem>
#include <stack>

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>

#include "lang/utility/Location.h"

namespace lang
{
    class Scope;
    class Context;
}

class SourceTree;
class Unit;
class Runtime;

/**
 * A class to simplify passing around the objects required for building the application.
 */
class CompileContext
{
  public:
    /**
     * Create a new compile context.
     * @param unit The unit to compile.
     * @param runtime The runtime.
     * @param c The llvm context.
     * @param m The llvm module.
     * @param ir The IR builder.
     * @param di The DI builder.
     * @param source_tree The source tree.
     */
    CompileContext(Unit&              unit,
                   Runtime&           runtime,
                   llvm::LLVMContext& c,
                   llvm::Module&      m,
                   llvm::IRBuilder<>& ir,
                   llvm::DIBuilder&   di,
                   SourceTree&        source_tree);

    /**
     * Get the unit.
     * @return The unit.
     */
    Unit& unit();

    /**
     * Get the runtime.
     * @return The runtime.
     */
    Runtime& runtime();

    /**
     * Get the language context in which the AST is built.
     * It contains all builtin types.
     * @return The language context.
     */
    lang::Context& types();

    /**
     * Get the llvmContext.
     * @return The llvmContext.
     */
    llvm::LLVMContext& llvmContext();

    /**
     * Get the module.
     * @return The module.
     */
    llvm::Module& llvmModule();

    /**
     * Get the ir builder.
     * @return The ir builder.
     */
    llvm::IRBuilder<>& ir();

    /**
     * Get the di builder.
     * @return The di builder.
     */
    llvm::DIBuilder& di();

    /**
     * Get the llvm compile unit.
     * @return The llvm compile unit.
     */
    llvm::DICompileUnit& llvmUnit();

    /**
     * Get the debug information for a source file that contains the given location.
     * @param location The location.
     * @return The debug information for the source file.
     */
    llvm::DIFile* getSourceFile(lang::Location location);

    /**
     * Get the path to the source file that contains the given location.
     * @param location The location.
     * @return The path to the source file.
     */
    std::filesystem::path getSourceFilePath(lang::Location location);

    /**
     * Set the current debug location.
     * @param location The source location.
     * @param scope The current scope.
     */
    void setDebugLocation(lang::Location location, lang::Scope& scope);

    /**
     * Reset the previous debug location.
     */
    void resetDebugLocation();

    /**
     * Get whether all debug locations were popped.
     * @return True if all locations were popped correctly.
     */
    bool allDebugLocationsPopped();

    /**
     * Get a string describing the current location in the source code.
     * @return The location string.
     */
    std::string getLocationString();

  private:
    Unit&                unit_;
    Runtime&             runtime_;
    llvm::LLVMContext&   context_;
    llvm::Module&        module_;
    llvm::IRBuilder<>&   ir_builder_;
    llvm::DIBuilder&     di_builder_;
    llvm::DICompileUnit* di_unit_ {nullptr};

    struct SourceFile {
        std::filesystem::path path;
        llvm::DIFile*         debug_info;
    };

    std::vector<SourceFile> source_files_ {};

    struct DebugLocation {
        llvm::DebugLoc di_location;
        lang::Location location;
    };

    DebugLocation current_debug_location_ {.location = lang::Location::global()};

    std::stack<DebugLocation, std::vector<DebugLocation>> debug_loc_stack_;
};

#endif
