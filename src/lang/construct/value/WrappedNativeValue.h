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
         * Create a new wrapped native value, the value can be set later.
         * @param type The type of the value.
         */
        explicit WrappedNativeValue(lang::ResolvingHandle<lang::Type> type);

        /**
         * Create a new wrapped native value.
         * @param type The type of the value.
         * @param value The native value to wrap.
         * @param context The compile context.
         */
        explicit WrappedNativeValue(lang::ResolvingHandle<lang::Type> type,
                                    llvm::Value*                      value,
                                    CompileContext&                   context);

        /**
         * Set the wrapped value if it is not already set.
         * @param value The native value to wrap.
         * @param context The compile context.
         */
        void setValue(llvm::Value* value, CompileContext& context);

        lang::ResolvingHandle<lang::Type> type() override;
        [[nodiscard]] lang::Type const&   type() const override;

        void                       buildNativeValue(CompileContext& context) override;

      private:
        lang::ResolvingHandle<lang::Type> type_;
    };
}
#endif
