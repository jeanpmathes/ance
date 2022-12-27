#ifndef ANCE_SRC_LANG_UTILITY_VALUES_H_
#define ANCE_SRC_LANG_UTILITY_VALUES_H_

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Value.h>

#include "lang/type/Type.h"
#include "lang/utility/ResolvingHandle.h"

class CompileContext;

namespace lang::values
{
    /**
     * Convert a native value to a content value.
     * @param type The type of the value.
     * @param native The native value.
     * @param context The current compile context.
     * @return The content value.
     */
    llvm::Value* nativeToContent(lang::Type const& type, llvm::Value* native, CompileContext& context);
    /**
     * Convert a content value to a native value.
     * @param type The type of the value.
     * @param content The content value.
     * @param context The current compile context.
     * @return The native value.
     */
    llvm::Value* contentToNative(lang::Type const& type, llvm::Value* content, CompileContext& context);

    /**
     * Get a clone of a value. Both values will then refer to the same native value.
     * @param value The value to clone. The native value must be built.
     * @return The new value.
     */
    Shared<lang::Value> clone(Shared<lang::Value> value);
}

#endif
