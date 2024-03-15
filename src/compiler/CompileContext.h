#ifndef ANCE_SRC_COMPILER_COMPILECONTEXT_H_
#define ANCE_SRC_COMPILER_COMPILECONTEXT_H_

#include <filesystem>
#include <stack>

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>

#include "compiler/Execution.h"
#include "lang/utility/Location.h"

namespace lang
{
    class Scope;
    class Context;
}

class SourceTree;
class Unit;
class Runtime;
class Execution;
class NativeBuild;

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
                   SourceTree&        source_tree,
                   NativeBuild**      native_build);

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
    lang::Context& ctx();

    /**
     * Get the current execution backend.
     * @return The execution backend.
     */
    Execution& exec();

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
    void setDebugLocation(lang::Location location, lang::Scope const& scope);

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
    std::unique_ptr<Execution> execution_;

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
