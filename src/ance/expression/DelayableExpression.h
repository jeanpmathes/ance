#ifndef ANCE_SRC_ANCE_EXPRESSION_DELAYABLEEXPRESSION_H_
#define ANCE_SRC_ANCE_EXPRESSION_DELAYABLEEXPRESSION_H_

#include "Expression.h"

#include "ance/construct/value/DelayedValue.h"
#include "ance/expression/BuildableExpression.h"

class DelayableExpression
    : public virtual Expression
    , public BuildableExpression
{
  public:
    virtual void buildValue(CompileContext* context) = 0;

    void build(CompileContext* context) final;

    ance::Value* getValue() override;

  protected:
    void setValue(ance::Value* value);

  private:
    ance::DelayedValue* value_ {new ance::DelayedValue(this)};
};

#endif
