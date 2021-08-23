#ifndef ANCE_SRC_COMPILER_RUNTIME_H_
#define ANCE_SRC_COMPILER_RUNTIME_H_

#include <string>

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>

class CompileContext;

namespace ance
{
    class Type;
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

  private:
    llvm::FunctionType* allocate_dynamic_type_ {nullptr};
    llvm::Function*     allocate_dynamic_ {nullptr};

    llvm::FunctionType* delete_dynamic_type_ {nullptr};
    llvm::Function*     delete_dynamic_ {nullptr};

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
    ance::Value* allocate(Allocator allocation, ance::Type* type, ance::Value* count, CompileContext* context);

    /**
     * Free dynamically allocated memory.
     * @param value A pointer to the memory.
     * @param delete_buffer Whether the memory is a single element or a buffer of multiple elements.
     * @param context The current compile context.
     */
    void deleteDynamic(ance::Value* value, bool delete_buffer, CompileContext* context);

  private:
    llvm::Value* allocateAutomatic(ance::Type* type, ance::Value* count, CompileContext* context);

    llvm::Value* allocateDynamic(ance::Type* type, ance::Value* count, CompileContext* context);
};

#endif
