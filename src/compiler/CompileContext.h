#ifndef ANCE_SRC_COMPILER_COMPILECONTEXT_H_
#define ANCE_SRC_COMPILER_COMPILECONTEXT_H_

#include <stack>

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>

#include "lang/utility/Location.h"

namespace lang
{
    class Scope;
}

class SourceTree;
class Application;
class Runtime;

/**
 * A class to simplify passing around the objects required for building the application.
 */
class CompileContext
{
  public:
    /**
     * Create a new compile context.
     * @param app The application.
     * @param runtime The runtime.
     * @param c The llvm context.
     * @param m The llvm module.
     * @param ir The IR builder.
     * @param di The DI builder.
     * @param source_tree The source tree.
     */
    CompileContext(Application&       app,
                   Runtime&           runtime,
                   llvm::LLVMContext& c,
                   llvm::Module&      m,
                   llvm::IRBuilder<>& ir,
                   llvm::DIBuilder&   di,
                   SourceTree&        source_tree);

    /**
     * Get the application.
     * @return The application.
     */
    Application* application();

    /**
     * Get the runtime.
     * @return The runtime.
     */
    Runtime* runtime();

    /**
     * Get the llvmContext.
     * @return The llvmContext.
     */
    llvm::LLVMContext* llvmContext();

    /**
     * Get the module.
     * @return The module.
     */
    llvm::Module* module();

    /**
     * Get the ir builder.
     * @return The ir builder.
     */
    llvm::IRBuilder<>* ir();

    /**
     * Get the di builder.
     * @return The di builder.
     */
    llvm::DIBuilder* di();

    /**
     * Get the compile unit.
     * @return The compile unit.
     */
    llvm::DICompileUnit* unit();

    /**
     * Get the debug information for a source file that contains the given location.
     * @param location The location.
     * @return The debug information for the source file.
     */
    llvm::DIFile* getSourceFile(lang::Location location);

    /**
     * Set the current debug location.
     * @param location The source location.
     * @param scope The current scope.
     */
    void setDebugLocation(lang::Location location, lang::Scope* scope);

    /**
     * Reset the previous debug location.
     */
    void resetDebugLocation();

    /**
     * Get whether all debug locations were popped.
     * @return True if all locations were popped correctly.
     */
    bool allDebugLocationsPopped();

  private:
    Application&         application_;
    Runtime&             runtime_;
    llvm::LLVMContext&   context_;
    llvm::Module&        module_;
    llvm::IRBuilder<>&   ir_builder_;
    llvm::DIBuilder&     di_builder_;
    llvm::DICompileUnit* unit_ {nullptr};

    std::vector<llvm::DIFile*> source_files_ {};

    std::stack<llvm::DebugLoc, std::vector<llvm::DebugLoc>> debug_loc_stack_;
};

#endif
