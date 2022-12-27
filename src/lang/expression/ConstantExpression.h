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
    [[nodiscard]] virtual Shared<lang::Constant> getConstantValue() = 0;

    /**
     * Get the constant value of this expression.
     * @return The constant value.
     */
    [[nodiscard]] virtual lang::Constant const& getConstantValue() const = 0;

    Shared<lang::Value>              getValue() override;
    [[nodiscard]] lang::Value const& getValue() const override;
};

#endif
