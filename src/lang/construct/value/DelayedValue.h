#ifndef ANCE_SRC_LANG_CONSTRUCT_VALUE_DELAYEDVALUE_H_
#define ANCE_SRC_LANG_CONSTRUCT_VALUE_DELAYEDVALUE_H_

#include "Value.h"

class DelayableExpression;

namespace lang
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
        explicit DelayedValue(Passed<DelayableExpression> expression);

        lang::ResolvingHandle<lang::Type> type() override;
        [[nodiscard]] lang::Type const&   type() const override;

        /**
         * Set the value to use. This method should be called once or never by the delayable expression.
         * @param value The value.
         */
        void setValue(Shared<lang::Value> value);

        void buildNativeValue(CompileContext& context) override;
        void buildContentValue(CompileContext& context) override;

      private:
        Passed<DelayableExpression>   expression_;
        Optional<Shared<lang::Value>> value_ {};
        bool                          built_ = false;
    };
}

#endif
