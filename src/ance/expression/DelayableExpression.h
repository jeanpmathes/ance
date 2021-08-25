#ifndef ANCE_SRC_ANCE_EXPRESSION_DELAYABLEEXPRESSION_H_
#define ANCE_SRC_ANCE_EXPRESSION_DELAYABLEEXPRESSION_H_

#include "Expression.h"

#include "ance/construct/value/DelayedValue.h"
#include "ance/expression/BuildableExpression.h"

/**
 * Interface of expressions providing the value for delayed values.
 */
class DelayableExpression
    : public virtual Expression
    , public BuildableExpression
{
  protected:
    /**
     * Create a new delayable expression with a given source location.
     * @param location The source location.
     */
    explicit DelayableExpression(ance::Location location);

  public:
    /**
     * Build the expression, and set the value if necessary.
     * @param context The current compile context.
     */
    virtual void buildValue(CompileContext* context) = 0;

    void build(CompileContext* context) final;

    ance::Value* getValue() override;

  protected:
    /**
     * Set the value of the delayable value.
     * @param value The value to use.
     */
    void setValue(ance::Value* value);

  private:
    ance::DelayedValue* value_ {new ance::DelayedValue(this)};
};

#endif
