#ifndef ANCE_SRC_ANCE_EXPRESSION_CONSTANTLITERAL_H_
#define ANCE_SRC_ANCE_EXPRESSION_CONSTANTLITERAL_H_

#include "ConstantExpression.h"

#include "lang/construct/constant/Constant.h"

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
    ConstantLiteral(std::shared_ptr<lang::Constant> constant, lang::Location location);

    lang::ResolvingHandle<lang::Type> type() override;

    bool validate(ValidationLogger& validation_logger) override;

    [[nodiscard]] std::shared_ptr<lang::Constant> getConstantValue() const override;

  private:
    std::shared_ptr<lang::Constant> constant_;
};

#endif
