#ifndef ANCE_SRC_LANG_CONSTRUCT_VALUE_VALUE_H_
#define ANCE_SRC_LANG_CONSTRUCT_VALUE_VALUE_H_

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>

#include "lang/utility/ResolvingHandle.h"
#include "lang/type/Type.h"

class Expression;
class CompileContext;

namespace lang
{
    /**
     * Represents any value that can be passed around in the final program.
     */
    class Value
    {
      public:
        /**
         * Get the type of the value.
         * @return The type.
         */
        virtual lang::ResolvingHandle<lang::Type> type() const = 0;

        /**
         * Build the native value. The native value is the value actually used in the IR.
         * @param context The native value.
         */
        virtual void buildNativeValue(CompileContext& context) = 0;
        /**
         * Build the content value. The content value is the value stored in the native value.
         * @param context The content value.
         */
        virtual void buildContentValue(CompileContext& context);

        /**
         * Get the native value. It must be built before accessing it.
         * @return The native value.
         */
        virtual llvm::Value* getNativeValue() = 0;
        /**
         * Get the content value. It must be built before accessing it.
         * @return The content value.
         */
        virtual llvm::Value* getContentValue();

        virtual ~Value() = default;

      private:
        llvm::Value* content_value_ {nullptr};
    };
}
#endif