#ifndef ANCE_SRC_LANG_EXPRESSION_BUILDABLEEXPRESSION_H_
#define ANCE_SRC_LANG_EXPRESSION_BUILDABLEEXPRESSION_H_

#include "Expression.h"

#include "lang/utility/Location.h"

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
    void build(CompileContext* context);

  protected:
    /**
    * Build the expression. This method should not be called, use build instead.
    * @param context The current compile context.
    */
    virtual void doBuild(CompileContext* context) = 0;
};

#endif
