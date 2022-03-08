#ifndef ANCE_SRC_LANG_EXPRESSION_CONSTANTLITERAL_H_
#define ANCE_SRC_LANG_EXPRESSION_CONSTANTLITERAL_H_

#include "ConstantExpression.h"

#include "lang/construct/constant/Constant.h"
#include "lang/Element.h"

/**
 * Wraps a constant.
 */
class ConstantLiteral
    : public ConstantExpression
    , public lang::Element<ConstantLiteral, ANCE_CONSTRUCTS>
{
  public:
    /**
     * Create a new constant literal.
     * @param constant The constant to wrap.
     * @param location The source location.
     */
    ConstantLiteral(std::shared_ptr<lang::Constant> constant, lang::Location location);

    [[nodiscard]] lang::Constant& constant() const;

    lang::ResolvingHandle<lang::Type> type() override;

    bool validate(ValidationLogger& validation_logger) override;

    [[nodiscard]] std::shared_ptr<lang::Constant> getConstantValue() const override;

  private:
    std::shared_ptr<lang::Constant> constant_;
};

#endif
