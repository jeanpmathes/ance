#ifndef ANCE_SRC_ANCE_EXPRESSION_BUILDABLEEXPRESSION_H_
#define ANCE_SRC_ANCE_EXPRESSION_BUILDABLEEXPRESSION_H_

#include "Expression.h"

#include "ance/utility/Location.h"

/**
 * An interface for expression that can be built.
 */
class BuildableExpression : public virtual Expression
{
  public:
    void setContainingScope(ance::Scope* scope) final;

    [[nodiscard]] ance::Scope* scope() const override;

    /**
     * Build the expression.
     * @param context The current compile context.
     */
    void build(CompileContext* context);

  protected:
    /**
     * Override this method to receive the containing scope.
     * @param scope The containing scope.
     */
    virtual void setScope(ance::Scope* scope);

    /**
    * Build the expression. This method should not be called, use build instead.
    * @param context The current compile context.
    */
    virtual void doBuild(CompileContext* context) = 0;

  private:
    ance::Scope* containing_scope_ {nullptr};
};

#endif
