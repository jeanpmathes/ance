#ifndef ANCE_SRC_COMPILER_RUNTIME_H_
#define ANCE_SRC_COMPILER_RUNTIME_H_

#include <string>

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>

#include "lang/construct/Function.h"
#include "lang/type/Type.h"
#include "lang/utility/ResolvingHandle.h"

class CompileContext;

namespace lang
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
    void init(CompileContext& context);

  private:
    CompileContext* context_ {nullptr};

    llvm::Function*              allocate_dynamic_ {nullptr};
    const static constexpr char* ALLOCATE_DYNAMIC_NAME = "__allocate__";

    llvm::Function*              delete_dynamic_ {nullptr};
    const static constexpr char* DELETE_DYNAMIC_NAME = "__free__";

    llvm::Function*              assertion_ {nullptr};
    const static constexpr char* ASSERTION_NAME = "__assert__";

    llvm::Function*              exit_ {nullptr};
    const static constexpr char* EXIT_NAME = "__exit__";

    llvm::Function*              abort_ {nullptr};
    const static constexpr char* ABORT_NAME = "__abort__";

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
    Shared<lang::Value> allocate(Allocator                         allocation,
                                 lang::ResolvingHandle<lang::Type> type,
                                 Optional<Shared<lang::Value>>     count,
                                 CompileContext&                   context);

    /**
     * Free dynamically allocated memory.
     * @param value A pointer to the memory.
     * @param delete_buffer Whether the memory is a single element or a buffer of multiple elements.
     * @param context The current compile context.
     */
    void deleteDynamic(Shared<lang::Value> value, bool delete_buffer, CompileContext& context);

    /**
     * Build an assertion.
     * @param value The boolean value to assert.
     * @param context The current compile context.
     */
    void buildAssert(Shared<lang::Value> value, CompileContext& context);

    /**
     * Build an exit.
     * @param value The exit code.
     * @param context The current compile context.
     */
    void buildExit(Shared<lang::Value> value, CompileContext& context);

  private:
    bool is_initialized_ {false};

    llvm::Value* allocateAutomatic(lang::ResolvingHandle<lang::Type> type,
                                   llvm::Value*                      count_value,
                                   CompileContext&                   context);

    llvm::Value* allocateDynamic(lang::ResolvingHandle<lang::Type> type,
                                 llvm::Value*                      count_value,
                                 CompileContext&                   context);
};

#endif
