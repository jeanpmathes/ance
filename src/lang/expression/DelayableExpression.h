#ifndef ANCE_SRC_LANG_EXPRESSION_DELAYABLEEXPRESSION_H_
#define ANCE_SRC_LANG_EXPRESSION_DELAYABLEEXPRESSION_H_

#include "BuildableExpression.h"
#include "Expression.h"

#include "lang/construct/value/DelayedValue.h"

/**
 * Interface of expressions providing the value for delayed values.
 */
class DelayableExpression
    : public virtual Expression
    , public BuildableExpression
{
  public:
    [[nodiscard]] std::shared_ptr<lang::Value> getValue() const override;

  protected:
    /**
     * Set the value of the delayable value.
     * @param value The value to use.
     */
    void setValue(const std::shared_ptr<lang::Value>& value);

  private:
    std::shared_ptr<lang::DelayedValue> value_ {std::make_shared<lang::DelayedValue>(this)};
};

#endif
