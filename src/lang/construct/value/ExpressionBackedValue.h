#ifndef ANCE_SRC_ANCE_CONSTRUCT_VALUE_EXPRESSIONBACKEDVALUE_H_
#define ANCE_SRC_ANCE_CONSTRUCT_VALUE_EXPRESSIONBACKEDVALUE_H_

#include "Value.h"

class BackingExpression;

namespace lang
{
    /**
     * A value backed by an expression that provides the native value.
     */
    class ExpressionBackedValue : public Value
    {
      public:
        /**
         * Create a new expression backed value.
         * @param expression The backing expression.
         */
        explicit ExpressionBackedValue(BackingExpression* expression);

        lang::ResolvingHandle<lang::Type> type() override;

        void         buildNativeValue(CompileContext* context) override;
        llvm::Value* getNativeValue() override;

      private:
        BackingExpression* expression_;
    };
}
#endif