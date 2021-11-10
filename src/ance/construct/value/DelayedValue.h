#ifndef ANCE_SRC_ANCE_CONSTRUCT_VALUE_DELAYEDVALUE_H_
#define ANCE_SRC_ANCE_CONSTRUCT_VALUE_DELAYEDVALUE_H_

#include "Value.h"

class DelayableExpression;

namespace ance
{
    /**
     * A value that uses another value provided by a delayable expression.
     */
    class DelayedValue : public Value
    {
      public:
        /**
         * Create a new delayed value.
         * @param expression The backing expression.
         */
        explicit DelayedValue(DelayableExpression* expression);

        ance::ResolvingHandle<ance::Type> type() override;

        /**
         * Set the value to use. This method should be called once or never by the delayable expression.
         * @param value The value.
         */
        void setValue(const std::shared_ptr<ance::Value>& value);

        void         buildNativeValue(CompileContext* context) override;
        llvm::Value* getNativeValue() override;

      private:
        DelayableExpression*         expression_;
        std::shared_ptr<ance::Value> value_ {};
    };
}

#endif
