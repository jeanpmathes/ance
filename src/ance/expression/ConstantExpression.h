#ifndef ANCE_SRC_ANCE_EXPRESSION_CONSTANTEXPRESSION_H_
#define ANCE_SRC_ANCE_EXPRESSION_CONSTANTEXPRESSION_H_

#include <llvm/IR/Constant.h>
#include <llvm/IR/LLVMContext.h>

#include "Expression.h"

namespace ance
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
    [[nodiscard]] virtual std::shared_ptr<ance::Constant> getConstantValue() const = 0;

    [[nodiscard]] std::shared_ptr<ance::Value> getValue() const override;
};

#endif