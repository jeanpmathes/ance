#ifndef ANCE_SRC_ANCE_EXPRESSION_CONSTANTLITERAL_H_
#define ANCE_SRC_ANCE_EXPRESSION_CONSTANTLITERAL_H_

#include "ConstantExpression.h"

/**
 * Wraps a constant.
 */
class ConstantLiteral : public ConstantExpression
{
  public:
    /**
     * Create a new constant literal.
     * @param constant The constant to wrap.
     * @param location The source location.
     */
    explicit ConstantLiteral(ance::Constant* constant, ance::Location location);

    ance::Type* type() override;

    void validate(ValidationLogger& validation_logger) override;

    [[nodiscard]] ance::Constant* getConstantValue() const override;

  private:
    ance::Constant* constant_;
};

#endif
