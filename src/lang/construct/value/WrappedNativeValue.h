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
         * Create a new wrapped native value with a default value for the given type.
         * @param type The type of the value.
         * @param context The compile context.
         * @return The new wrapped native value.
         */
        static Shared<lang::Value> makeDefault(lang::ResolvingHandle<lang::Type> type, CompileContext& context);

        /**
         * Set the wraped value if it is not already set.
         * @param value The native value to wrap.
         */
        void setValue(llvm::Value* value);

        lang::ResolvingHandle<lang::Type> type() override;
        [[nodiscard]] lang::Type const&   type() const override;

        void                       buildNativeValue(CompileContext& context) override;
        [[nodiscard]] llvm::Value* getNativeValue() const override;

      private:
        lang::ResolvingHandle<lang::Type> type_;
        llvm::Value*                      value_;
    };
}
#endif
