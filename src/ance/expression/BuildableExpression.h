#ifndef ANCE_SRC_ANCE_EXPRESSION_BUILDABLEEXPRESSION_H_
#define ANCE_SRC_ANCE_EXPRESSION_BUILDABLEEXPRESSION_H_

#include "Expression.h"

/**
 * An interface for expression that can be built.
 */
class BuildableExpression : public virtual Expression
{
  public:
    /**
     * Build the expression.
     * @param context The current compile context.
     */
    virtual void build(CompileContext* context) = 0;
};

#endif
