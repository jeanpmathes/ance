#ifndef ANCE_SRC_ANCE_EXPRESSION_ROUGHCAST_H_
#define ANCE_SRC_ANCE_EXPRESSION_ROUGHCAST_H_

#include "Expression.h"

namespace ance
{
    class Scope;
}

/**
 * A rough cast, casting between two different types that use the same native type.
 */
class RoughCast : public Expression
{
  public:
    /**
     * Create a new rough cast.
     * @param target_type The target type.
     * @param expression The expression providing the value to cast.
     */
    RoughCast(ance::Type* target_type, Expression* expression);

    void setContainingScope(ance::Scope* scope) override;

    ance::Type* type() override;

    [[nodiscard]] ance::Value* getValue() const override;

    ~RoughCast() override;

  private:
    ance::Type*  target_type_;
    Expression*  expression_;
    ance::Value* return_value_;
};

#endif
