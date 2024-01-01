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

    /**
     * Check whether a name is reserved by the runtime.
     * A reserved name cannot be used by a function that is not mangled, except if the runtime is excluded.
     * @param name The name to check.
     * @return True if the name is reserved.
     */
    [[nodiscard]] static bool isNameReserved(lang::Identifier const& name);

  private:
    Execution::Function          allocate_dynamic_ {};
    const static constexpr char* ALLOCATE_DYNAMIC_NAME = "__allocate__";

    Execution::Function          delete_dynamic_ {};
    const static constexpr char* DELETE_DYNAMIC_NAME = "__free__";

    Execution::Function          assertion_ {};
    const static constexpr char* ASSERTION_NAME = "__assert__";

    Execution::Function          abort_ {};
    const static constexpr char* ABORT_NAME = "__abort__";

    inline static std::vector<std::string> reserved_names_ {ALLOCATE_DYNAMIC_NAME,
                                                            DELETE_DYNAMIC_NAME,
                                                            ASSERTION_NAME,
                                                            ABORT_NAME};

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
     * @param address A pointer to the memory.
     * @param delete_buffer Whether the memory is a single element or a buffer of multiple elements.
     * @param context The current compile context.
     */
    void deleteDynamic(Shared<lang::Value> address, bool delete_buffer, CompileContext& context);

    /**
     * Build an assertion. Only performed when assertions are enabled.
     * @param value The boolean value to assert.
     * @param description The description of the assertion.
     * @param context The current compile context.
     */
    void buildAssert(Shared<lang::Value> value, std::string const& description, CompileContext& context);

    /**
     * Build an abort.
     * @param reason The description of the abort.
     * @param context The current compile context.
     */
    void buildAbort(std::string const& reason, CompileContext& context);

  private:
    bool is_initialized_ {false};

    Shared<lang::Value> allocateAutomatic(lang::ResolvingHandle<lang::Type> type,
                                          Shared<lang::Value>               count,
                                          CompileContext&                   context);

    Shared<lang::Value> allocateDynamic(lang::ResolvingHandle<lang::Type> type,
                                        Shared<lang::Value>               count,
                                        bool                              is_buffer,
                                        CompileContext&                   context);
};

#endif
