#ifndef ANCE_SRC_LANG_EXPRESSION_CONSTANTLITERAL_H_
#define ANCE_SRC_LANG_EXPRESSION_CONSTANTLITERAL_H_

#include "ConstantExpression.h"

#include "lang/Element.h"
#include "lang/construct/constant/Constant.h"

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

    [[nodiscard]] std::optional<lang::ResolvingHandle<lang::Type>> tryGetType() const override;

    bool validate(ValidationLogger& validation_logger) const override;

    [[nodiscard]] Expansion expandWith(Expressions subexpressions) const override;

    [[nodiscard]] std::shared_ptr<lang::Constant> getConstantValue() const override;

  private:
    std::shared_ptr<lang::Constant> constant_;
};

#endif
