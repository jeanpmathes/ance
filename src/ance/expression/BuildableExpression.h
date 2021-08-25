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

    void setContainingScope(ance::Scope* scope) final;

  protected:
    /**
     * Override this method to receive the containing scope.
     * @param scope The containing scope.
     */
    virtual void setScope(ance::Scope* scope);

  private:
    ance::Location location_;
    ance::Scope*   containing_scope_;
};

#endif
