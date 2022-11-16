#ifndef ANCE_SRC_LANG_CONSTRUCT_VALUE_WRAPPEDNATIVEVALUE_H_
#define ANCE_SRC_LANG_CONSTRUCT_VALUE_WRAPPEDNATIVEVALUE_H_

#include "Value.h"

#include "lang/type/Type.h"
#include "lang/utility/ResolvingHandle.h"

namespace lang
{
    /**
     * A value wrapping a native value.
     */
    class WrappedNativeValue : public Value
    {
      public:
        /**
         * Create a new wrapped native value.
         * @param type The type of the value.
         * @param value The native value to wrap, can be set later.
         */
        explicit WrappedNativeValue(lang::ResolvingHandle<lang::Type> type, llvm::Value* value = nullptr);

        /**
         * Set the wraped value if it is not already set.
         * @param value The native value to wrap.
         */
        void setValue(llvm::Value* value);

        lang::ResolvingHandle<lang::Type> type() const override;

        void         buildNativeValue(CompileContext& context) override;
        llvm::Value* getNativeValue() override;

      private:
        lang::ResolvingHandle<lang::Type> type_;
        llvm::Value*                      value_;
    };
}
#endif
