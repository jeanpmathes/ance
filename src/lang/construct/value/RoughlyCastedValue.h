#ifndef ANCE_SRC_LANG_CONSTRUCT_VALUE_ROUGHLYCASTEDVALUE_H_
#define ANCE_SRC_LANG_CONSTRUCT_VALUE_ROUGHLYCASTEDVALUE_H_

#include "Value.h"

#include "lang/type/Type.h"
#include "lang/utility/ResolvingHandle.h"

namespace lang
{
    /**
     * Create a value that is result of a rough as.
     */
    class RoughlyCastedValue : public Value
    {
      public:
        /**
         * Create a new roughly casted value.
         * @param target_type The target type.
         * @param original The original value.
         * @param context The compile context.
         */
        RoughlyCastedValue(lang::ResolvingHandle<lang::Type> target_type,
                           Shared<lang::Value>               original,
                           CompileContext&                   context);

        lang::ResolvingHandle<lang::Type> type() override;
        [[nodiscard]] lang::Type const&   type() const override;

        void                       buildNativeValue(CompileContext& context) override;
        void buildContentValue(CompileContext& context) override;

      private:
        lang::ResolvingHandle<lang::Type> target_type_;
        Shared<lang::Value>               original_;
    };
}

#endif
