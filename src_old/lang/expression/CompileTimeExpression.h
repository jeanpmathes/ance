#ifndef ANCE_SRC_LANG_EXPRESSION_COMPILETIMEEXPRESSION_H_
#define ANCE_SRC_LANG_EXPRESSION_COMPILETIMEEXPRESSION_H_

#include "Expression.h"

/**
 * An expression that can be evaluated at compile-time.
 * Note that runtime evaluation is not excluded.
 */
class CompileTimeExpression : public virtual Expression
{
  public:
    [[nodiscard]] lang::CMP rootCMP() const override;
};

#endif
