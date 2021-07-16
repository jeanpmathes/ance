#ifndef ANCE_SRC_ANCE_EXPRESSION_ROUGHCAST_H_
#define ANCE_SRC_ANCE_EXPRESSION_ROUGHCAST_H_

#include "Expression.h"

namespace ance
{
    class Scope;
}

class RoughCast : public Expression
{
  public:
    RoughCast(ance::Type* target_type, Expression* expression);

    void setScope(ance::Scope* scope) override;

    ance::Type* type() override;

    ance::Value* getValue() override;

    ~RoughCast() override;

  private:
    ance::Type*  target_type_;
    Expression*  expression_;
    ance::Value* return_value_;
};

#endif
