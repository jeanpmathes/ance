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
    Shared<lang::Value>              getValue() override;
    [[nodiscard]] lang::Value const& getValue() const override;

  protected:
    /**
     * Set the value of the delayable value.
     * @param value The value to use.
     */
    void setValue(Shared<lang::Value> value);

  private:
    Shared<lang::DelayedValue> delayed_value_ {makeShared<lang::DelayedValue>(pass(*this))};
    Shared<lang::Value>        value_ {delayed_value_};
};

#endif
