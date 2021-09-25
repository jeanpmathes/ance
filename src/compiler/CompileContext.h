#ifndef ANCE_SRC_COMPILER_COMPILECONTEXT_H_
#define ANCE_SRC_COMPILER_COMPILECONTEXT_H_

#include <stack>

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>

#include "ance/utility/Location.h"

namespace ance
{
    class Scope;
}

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
     * @param unit The compile unit.
     * @param src_file The source file.
     */
    CompileContext(Application*         app,
                   Runtime*             runtime,
                   llvm::LLVMContext*   c,
                   llvm::Module*        m,
                   llvm::IRBuilder<>*   ir,
                   llvm::DIBuilder*     di,
                   llvm::DICompileUnit* unit,
                   llvm::DIFile*        src_file);

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
     * Get the source file.
     * @return The source file.
     */
    llvm::DIFile* sourceFile();

    /**
     * Set the current debug location.
     * @param location The source location.
     * @param scope The current scope.
     */
    void setDebugLocation(ance::Location location, ance::Scope* scope);

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
    Application*         application_;
    Runtime*             runtime_;
    llvm::LLVMContext*   context_;
    llvm::Module*        module_;
    llvm::IRBuilder<>*   ir_builder_;
    llvm::DIBuilder*     di_builder_;
    llvm::DICompileUnit* unit_;
    llvm::DIFile*        src_file_;

    std::stack<llvm::DebugLoc, std::vector<llvm::DebugLoc>> debug_loc_stack_;
};

#endif