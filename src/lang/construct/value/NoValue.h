#ifndef ANCE_SRC_LANG_CONSTRUCT_VALUE_NOVALUE_H_
#define ANCE_SRC_LANG_CONSTRUCT_VALUE_NOVALUE_H_

#include "lang/construct/value/Value.h"

#include "lang/expression/UnexpandedExpression.h"

namespace lang
{
    /**
     * Represents a value produced by unexpanded expressions.
     * Using a NoValue is valid for validation, but not when building.
     */
    class NoValue : public lang::Value
    {
      public:
        explicit NoValue(UnexpandedExpression& unexpanded_expression);
        ~NoValue() override = default;

        lang::ResolvingHandle<lang::Type> type() override;

        void buildNativeValue(CompileContext* context) override;
        void buildContentValue(CompileContext* context) override;

        llvm::Value* getNativeValue() override;
        llvm::Value* getContentValue() override;

      private:
        UnexpandedExpression& unexpanded_expression_;
    };
}

#endif
