#ifndef ANCE_SRC_LANG_CONSTRUCT_VALUE_VALUE_H_
#define ANCE_SRC_LANG_CONSTRUCT_VALUE_VALUE_H_

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>

#include "lang/utility/ResolvingHandle.h"

class Expression;
class CompileContext;

namespace lang
{
    class Type;
}

namespace lang
{
    /**
     * Represents any value that can be passed around in the final program.
     * The value provides two ways of accessing the actual value:
     * - The native value is a pointer to a stack allocated value.
     * - The content value is the value stored on the stack or in a register.
     * Both are converted to each other using load and store operations.
     */
    class Value
    {
      public:
        /**
         * Get the type of the value.
         * @return The type.
         */
        virtual lang::ResolvingHandle<lang::Type> type() = 0;

        /**
         * Get the type of the value.
         * @return The type.
         */
        [[nodiscard]] virtual lang::Type const& type() const = 0;

        /**
         * Build the native value. The native value is the value actually used in the IR.
         * @param context The native value.
         */
        virtual void buildNativeValue(CompileContext& context);
        /**
         * Build the content value. The content value is the value stored in the native value.
         * @param context The content value.
         */
        virtual void buildContentValue(CompileContext& context);

        /**
         * Get the native value. It must be built before accessing it.
         * @return The native value.
         */
        [[nodiscard]] llvm::Value* getNativeValue() const;
        /**
         * Get the content value. It must be built before accessing it.
         * @return The content value.
         */
        [[nodiscard]] llvm::Value* getContentValue() const;

        virtual ~Value() = default;

      protected:
        llvm::Value* native_value_ {nullptr};
        llvm::Value* content_value_ {nullptr};
    };
}
#endif
