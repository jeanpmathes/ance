#ifndef ANCE_SRC_LANG_CONSTRUCT_VALUE_NOVALUE_H_
#define ANCE_SRC_LANG_CONSTRUCT_VALUE_NOVALUE_H_

#include "lang/construct/value/Value.h"

class UnexpandedExpression;

namespace lang
{
    /**
     * Represents a value produced by unexpanded expressions.
     * Using a NoValue is valid for validation, but not when building.
     */
    class NoValue : public lang::Value
    {
      public:
        explicit NoValue(Passed<UnexpandedExpression> unexpanded_expression);
        ~NoValue() override = default;

        lang::ResolvingHandle<lang::Type> type() override;
        [[nodiscard]] lang::Type const&   type() const override;

        void buildNativeValue(CompileContext& context) override;
        void buildContentValue(CompileContext& context) override;

      private:
        Passed<UnexpandedExpression> unexpanded_expression_;
    };
}

#endif
