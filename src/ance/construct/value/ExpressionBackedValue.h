#ifndef ANCE_SRC_ANCE_CONSTRUCT_VALUE_EXPRESSIONBACKEDVALUE_H_
#define ANCE_SRC_ANCE_CONSTRUCT_VALUE_EXPRESSIONBACKEDVALUE_H_

#include "BackingExpression.h"
#include "Value.h"

namespace ance
{
    class ExpressionBackedValue : public Value
    {
      public:
        explicit ExpressionBackedValue(BackingExpression* expression);

        ance::Type* type() override;

        void buildNativeValue(CompileContext* context) override;

        llvm::Value* getNativeValue() override;

      private:
        BackingExpression* expression_;
    };
}
#endif