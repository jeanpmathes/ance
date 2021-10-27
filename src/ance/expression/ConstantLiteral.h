#ifndef ANCE_SRC_ANCE_EXPRESSION_CONSTANTLITERAL_H_
#define ANCE_SRC_ANCE_EXPRESSION_CONSTANTLITERAL_H_

#include "ConstantExpression.h"

#include "ance/construct/constant/Constant.h"

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
    ConstantLiteral(std::shared_ptr<ance::Constant> constant, ance::Location location);

    ance::Type* type() override;

    bool validate(ValidationLogger& validation_logger) override;

    [[nodiscard]] std::shared_ptr<ance::Constant> getConstantValue() const override;

  private:
    std::shared_ptr<ance::Constant> constant_;
};

#endif
