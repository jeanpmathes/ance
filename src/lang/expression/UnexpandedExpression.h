#ifndef ANCE_SRC_LANG_EXPRESSION_UNEXPANDEDEXPRESSION_H_
#define ANCE_SRC_LANG_EXPRESSION_UNEXPANDEDEXPRESSION_H_

#include "lang/expression/Expression.h"

/**
 * An expression that cannot be build on its own, as it has to be expanded.
 * This means the expression is syntactic sugar.
 */
class UnexpandedExpression : public Expression
{
  public:
    explicit UnexpandedExpression(lang::Location location);

    Shared<lang::Value>              getValue() override;
    [[nodiscard]] lang::Value const& getValue() const override;

  private:
    Shared<lang::Value> value_;
};

#endif
