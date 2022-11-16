#ifndef ANCE_SRC_LANG_CONSTRUCT_VALUE_ROUGHLYCASTEDVALUE_H_
#define ANCE_SRC_LANG_CONSTRUCT_VALUE_ROUGHLYCASTEDVALUE_H_

#include "Value.h"

#include "lang/type/Type.h"
#include "lang/utility/ResolvingHandle.h"

namespace lang
{
    /**
     * Create a value that is result of a rough cast.
     */
    class RoughlyCastedValue : public Value
    {
      public:
        /**
         * Create a new roughly casted value.
         * @param target_type The target type.
         * @param original The original value.
         */
        RoughlyCastedValue(lang::ResolvingHandle<lang::Type> target_type, std::shared_ptr<lang::Value> original);

        lang::ResolvingHandle<lang::Type> type() const override;

        void         buildNativeValue(CompileContext& context) override;
        llvm::Value* getNativeValue() override;

      private:
        lang::ResolvingHandle<lang::Type> target_type_;
        std::shared_ptr<lang::Value>      original_;
    };
}

#endif
