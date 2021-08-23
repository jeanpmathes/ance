#ifndef ANCE_SRC_ANCE_CONSTRUCT_VALUE_WRAPPEDNATIVEVALUE_H_
#define ANCE_SRC_ANCE_CONSTRUCT_VALUE_WRAPPEDNATIVEVALUE_H_

#include "Value.h"

namespace ance
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
        explicit WrappedNativeValue(ance::Type* type, llvm::Value* value = nullptr);

        /**
         * Set the wraped value if it is not already set.
         * @param value The native value to wrap.
         */
        void setValue(llvm::Value* value);

        ance::Type* type() override;

        void buildNativeValue(CompileContext* context) override;
        llvm::Value* getNativeValue() override;

      private:
        ance::Type*  type_;
        llvm::Value* value_;
    };
}
#endif
