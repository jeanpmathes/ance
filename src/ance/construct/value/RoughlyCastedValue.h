#ifndef ANCE_SRC_ANCE_CONSTRUCT_VALUE_ROUGHLYCASTEDVALUE_H_
#define ANCE_SRC_ANCE_CONSTRUCT_VALUE_ROUGHLYCASTEDVALUE_H_

#include "Value.h"

#include "ance/type/Type.h"
#include "ance/utility/ResolvingHandle.h"

namespace ance
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
        RoughlyCastedValue(ance::ResolvingHandle<ance::Type> target_type, std::shared_ptr<ance::Value> original);

        ance::ResolvingHandle<ance::Type> type() override;

        void         buildNativeValue(CompileContext* context) override;
        llvm::Value* getNativeValue() override;

      private:
        ance::ResolvingHandle<ance::Type> target_type_;
        std::shared_ptr<ance::Value>      original_;
    };
}

#endif
