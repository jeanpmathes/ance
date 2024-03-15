#ifndef ANCE_SRC_LANG_EXPRESSION_LITERALEXPRESSION_H_
#define ANCE_SRC_LANG_EXPRESSION_LITERALEXPRESSION_H_

#include "Expression.h"

#include "lang/Element.h"
#include "lang/construct/constant/LiteralConstant.h"

/**
 * An expression that contains a constant value, provided by a literal.
 */
class LiteralExpression
    : public Expression
    , public lang::Element<LiteralExpression, ANCE_CONSTRUCTS>
{
  public:
    /**
     * Create a new constant literal.
     * @param constant The constant to wrap.
     * @param location The source location.
     */
    LiteralExpression(Shared<lang::LiteralConstant> constant, lang::Location location);

    [[nodiscard]] lang::LiteralConstant const& constant() const;
    [[nodiscard]] Shared<lang::Constant> constant(CompileContext& context);

    bool validate(ValidationLogger& validation_logger) const override;

    [[nodiscard]] Expansion expandWith(Expressions subexpressions, lang::Context& new_context) const override;

  protected:
    void defineType(lang::ResolvingHandle<lang::Type> type) override;

  public:
    ~LiteralExpression() override;

  private:
    Shared<lang::LiteralConstant> constant_;
};

#endif
