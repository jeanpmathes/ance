#ifndef ANCE_SRC_ANCE_EXPRESSION_CONSTANTLITERAL_H_
#define ANCE_SRC_ANCE_EXPRESSION_CONSTANTLITERAL_H_

#include "ConstantExpression.h"

class ConstantLiteral : public ConstantExpression
{
  public:
    explicit ConstantLiteral(ance::Constant* constant);

    ance::Type* type() override;

    ance::Constant* getConstantValue() override;

  private:
    ance::Constant* constant_;
};

#endif
