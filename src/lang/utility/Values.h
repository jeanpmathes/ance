#ifndef ANCE_SRC_ANCE_UTILITY_VALUES_H_
#define ANCE_SRC_ANCE_UTILITY_VALUES_H_

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Value.h>

#include "lang/type/Type.h"
#include "lang/utility/ResolvingHandle.h"

class CompileContext;

namespace lang
{
    /**
     * A utility class to convert between native and content values.
     */
    class Values
    {
      public:
        /**
         * Convert a native value to a content value.
         * @param type The type of the value.
         * @param native The native value.
         * @param context The current compile context.
         * @return The content value.
         */
        static llvm::Value* nativeToContent(lang::ResolvingHandle<lang::Type> type,
                                            llvm::Value*                      native,
                                            CompileContext*                   context);
        /**
         * Convert a content value to a native value.
         * @param type The type of the value.
         * @param content The content value.
         * @param context The current compile context.
         * @return The native value.
         */
        static llvm::Value* contentToNative(lang::ResolvingHandle<lang::Type> type,
                                            llvm::Value*                      content,
                                            CompileContext*                   context);
    };
}

#endif
