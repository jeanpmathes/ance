#ifndef ANCE_SRC_LANG_CONSTRUCT_VALUE_WRAPPEDCONTENTVALUE_H_
#define ANCE_SRC_LANG_CONSTRUCT_VALUE_WRAPPEDCONTENTVALUE_H_

#include "Value.h"

#include "lang/type/Type.h"
#include "lang/utility/ResolvingHandle.h"

namespace lang
{
    /**
     * A value wrapping a content value.
     */
    class WrappedContentValue : public Value
    {
      public:
        /**
         * Create a new wrapped native value, the value can be set later.
         * @param type The type of the value.
         */
        explicit WrappedContentValue(lang::ResolvingHandle<lang::Type> type);

        /**
         * Create a new wrapped native value.
         * @param type The type of the value.
         * @param value The native value to wrap.
         * @param context The compile context.
         */
        explicit WrappedContentValue(lang::ResolvingHandle<lang::Type> type,
                                     llvm::Value*                      value,
                                     CompileContext&                   context);

        /**
         * Set the wrapped value if it is not already set.
         * @param value The native value to wrap.
         * @param context The compile context.
         */
        void setValue(llvm::Value* value, CompileContext& context);

        /**
         * Set the wrapped value without checking if the type matches.
         * @param value The native value to wrap.
         */
        void setValueUnchecked(llvm::Value* value);

        lang::ResolvingHandle<lang::Type> type() override;
        [[nodiscard]] lang::Type const&   type() const override;

        void buildContentValue(CompileContext& context) override;

      private:
        lang::ResolvingHandle<lang::Type> type_;
    };
}
#endif
