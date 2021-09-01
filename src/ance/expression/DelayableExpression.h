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
  public:
    [[nodiscard]] ance::Value* getValue() const override;

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
