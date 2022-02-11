#ifndef ANCE_SRC_LANG_EXPRESSION_CONSTANTEXPRESSION_H_
#define ANCE_SRC_LANG_EXPRESSION_CONSTANTEXPRESSION_H_

#include <llvm/IR/Constant.h>
#include <llvm/IR/LLVMContext.h>

#include "Expression.h"

namespace lang
{
    class Constant;
}

/**
 * An expression that can return constants.
 */
class ConstantExpression : public virtual Expression
{
  public:
    /**
     * Get the constant value of this expression.
     * @return The constant value.
     */
    [[nodiscard]] virtual std::shared_ptr<lang::Constant> getConstantValue() const = 0;

    [[nodiscard]] std::shared_ptr<lang::Value> getValue() const override;
};

#endif