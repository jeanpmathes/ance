#ifndef ANCE_SRC_COMPILER_RUNTIME_H_
#define ANCE_SRC_COMPILER_RUNTIME_H_

#include <string>

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>

#include "lang/construct/Function.h"
#include "lang/type/Type.h"
#include "lang/utility/ResolvingHandle.h"

class Execution;

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
     * @param exec The current execution context.
     */
    void init(Execution& exec);

    /**
     * Check whether a name is reserved by the runtime.
     * A reserved name cannot be used by a function that is not mangled, except if the runtime is excluded.
     * @param name The name to check.
     * @return True if the name is reserved.
     */
    [[nodiscard]] static bool isNameReserved(lang::Identifier const& name);

  private:
    lang::Function*              allocate_dynamic_     = nullptr;
    static constexpr char const* ALLOCATE_DYNAMIC_NAME = "__allocate__";

    lang::Function*              delete_dynamic_     = nullptr;
    static constexpr char const* DELETE_DYNAMIC_NAME = "__free__";

    lang::Function*              assertion_     = nullptr;
    static constexpr char const* ASSERTION_NAME = "__assert__";

    lang::Function*              abort_     = nullptr;
    static constexpr char const* ABORT_NAME = "__abort__";

    inline static std::vector<std::string> reserved_names_ {ALLOCATE_DYNAMIC_NAME,
                                                            DELETE_DYNAMIC_NAME,
                                                            ASSERTION_NAME,
                                                            ABORT_NAME};

    std::vector<lang::Function*> functions_;

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
     * @param exec The current execution context.
     * @return A pointer to the allocated memory.
     */
    Shared<lang::Value> allocate(Allocator                     allocation,
                                 lang::Type const&             type,
                                 Optional<Shared<lang::Value>> count,
                                 Execution&                    exec);

    /**
     * Free dynamically allocated memory.
     * @param address A pointer to the memory.
     * @param delete_buffer Whether the memory is a single element or a buffer of multiple elements.
     * @param exec The current execution context.
     */
    void deleteDynamic(Shared<lang::Value> address, bool delete_buffer, Execution& exec);

    /**
     * Build an assertion. Only performed when assertions are enabled.
     * @param value The boolean value to assert.
     * @param description The description of the assertion.
     * @param exec The current execution context.
     */
    void buildAssert(Shared<lang::Value> value, std::string const& description, Execution& exec);

    /**
     * Build an abort.
     * @param reason The description of the abort.
     * @param exec The current execution context.
     */
    void buildAbort(std::string const& reason, Execution& exec);

  private:
    bool is_initialized_ {false};

    Shared<lang::Value> allocateAutomatic(lang::Type const& type, Shared<lang::Value> count, Execution& exec);

    Shared<lang::Value> allocateDynamic(lang::Type const&   type,
                                        Shared<lang::Value> count,
                                        bool                is_buffer,
                                        Execution&          exec);
};

#endif
