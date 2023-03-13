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
    ConstantLiteral(Shared<lang::Constant> constant, lang::Location location);

    [[nodiscard]] lang::Constant const& constant() const;

    bool validate(ValidationLogger& validation_logger) const override;

    [[nodiscard]] Expansion expandWith(Expressions subexpressions, lang::Context& new_context) const override;

    Shared<lang::Constant>              getConstantValue() override;
    [[nodiscard]] lang::Constant const& getConstantValue() const override;

  protected:
    void defineType(lang::ResolvingHandle<lang::Type> type) override;

  public:
    ~ConstantLiteral() override;

  private:
    Shared<lang::Constant> constant_;
};

#endif
