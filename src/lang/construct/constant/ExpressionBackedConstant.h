#ifndef ANCE_SRC_LANG_CONSTRUCT_CONSTANT_EXPRESSIONBACKEDCONSTANT_H_
#define ANCE_SRC_LANG_CONSTRUCT_CONSTANT_EXPRESSIONBACKEDCONSTANT_H_

#include "Constant.h"

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>

class BackingConstantExpression;

namespace lang
{
    /**
     * An interface for constants that use expressions to provide their value.
     */
    class ExpressionBackedConstant : public Constant
    {
      public:
        /**
         * Create a new expression backed constant.
         * @param expression The backing constant expression.
         */
        explicit ExpressionBackedConstant(BackingConstantExpression& expression);

        [[nodiscard]] std::string toString() const override;
        [[nodiscard]] Expression* getBackingExpression() const override;

        lang::ResolvingHandle<lang::Type> type() override;
        llvm::Constant*                   buildContent(llvm::Module* m) override;

        bool equals(const lang::Constant* other) const override;

      private:
        BackingConstantExpression& expression_;
    };
}
#endif
