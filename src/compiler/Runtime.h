#ifndef ANCE_SRC_COMPILER_RUNTIME_H_
#define ANCE_SRC_COMPILER_RUNTIME_H_

#include <string>

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>

#include "ance/type/Type.h"
#include "ance/utility/ResolvingHandle.h"
#include "ance/construct/Function.h"

class CompileContext;

namespace ance
{
    class Value;
}

/**
 * The runtime provides the language with operations that depend on the OS.
 */
class Runtime
{
  public:
    /**
     * Initialize the runtime.
     * @param context The current compile context.
     */
    void init(CompileContext* context);

    /**
     * Set the exit point.
     * @param exit The exit function, defined for the current application.
     */
    void setExit(ance::ResolvingHandle<ance::Function> exit);

  private:
    CompileContext* context_ {nullptr};

    llvm::FunctionType* allocate_dynamic_type_ {nullptr};
    llvm::Function*     allocate_dynamic_ {nullptr};

    llvm::FunctionType* delete_dynamic_type_ {nullptr};
    llvm::Function*     delete_dynamic_ {nullptr};

    llvm::FunctionType* assertion_type_ {nullptr};
    llvm::Function*     assertion_ {nullptr};

  public:
    /**
     * Types of allocators.
     */
    enum Allocator
    {
        /**
         * Memory allocated is freed automatically after the control flow exits the holding scope.
         */
        AUTOMATIC,
        /**
         * Memory must be freed manually.
         */
        DYNAMIC
    };

    /**
     * Allocate memory.
     * @param allocation The allocator to use.
     * @param type The type of the value to allocate memory for.
     * @param count The number of elements to allocate.
     * @param context The current compile context.
     * @return A pointer to the allocated memory.
     */
    std::shared_ptr<ance::Value> allocate(Allocator                           allocation,
                                          ance::ResolvingHandle<ance::Type>   type,
                                          const std::shared_ptr<ance::Value>& count,
                                          CompileContext*                     context);

    /**
     * Free dynamically allocated memory.
     * @param value A pointer to the memory.
     * @param delete_buffer Whether the memory is a single element or a buffer of multiple elements.
     * @param context The current compile context.
     */
    void deleteDynamic(const std::shared_ptr<ance::Value>& value, bool delete_buffer, CompileContext* context);

    /**
     * Build an assertion.
     * @param value The boolean value to assert.
     * @param context The current compile context.
     */
    void buildAssert(const std::shared_ptr<ance::Value>& value, CompileContext* context);

  private:
    llvm::Value* allocateAutomatic(ance::ResolvingHandle<ance::Type>   type,
                                   const std::shared_ptr<ance::Value>& count,
                                   CompileContext*                     context);

    llvm::Value* allocateDynamic(ance::ResolvingHandle<ance::Type>   type,
                                 const std::shared_ptr<ance::Value>& count,
                                 CompileContext*                     context);
};

#endif
