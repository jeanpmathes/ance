#ifndef ANCE_SRC_ANCE_EXPRESSION_BUILDABLEEXPRESSION_H_
#define ANCE_SRC_ANCE_EXPRESSION_BUILDABLEEXPRESSION_H_

#include "Expression.h"

#include "ance/utility/Location.h"

/**
 * An interface for expression that can be built.
 */
class BuildableExpression : public virtual Expression
{
  protected:
    /**
     * Create a buildable expression with the given source location.
     * @param location The source location.
     */
    explicit BuildableExpression(ance::Location location);

  public:
    /**
     * Build the expression.
     * @param context The current compile context.
     */
    virtual void build(CompileContext* context) = 0;

  private:
    ance::Location location_;
};

#endif
