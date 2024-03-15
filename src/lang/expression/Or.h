#ifndef ANCE_SRC_LANG_EXPRESSION_OR_H_
#define ANCE_SRC_LANG_EXPRESSION_OR_H_

#include "Expression.h"

#include "lang/Element.h"

/**
 * Logical 'or' expression, with short-circuit evaluation.
 */
class Or
    : public Expression
    , public lang::Element<Or, ANCE_CONSTRUCTS>
{
  public:
    /**
     * Create a new logical 'or' expression.
     * @param negate Whether to negate the result.
     * @param left The left operand.
     * @param right The right operand.
     * @param location The source location of the operation.
     */
    Or(bool negate, Owned<Expression> left, Owned<Expression> right, lang::Location location);

    [[nodiscard]] bool              negate() const;
    [[nodiscard]] Expression const& left() const;
    [[nodiscard]] Expression const& right() const;

  public:
    bool validate(ValidationLogger& validation_logger) const override;

    [[nodiscard]] Expansion expandWith(Expressions subexpressions, lang::Context& new_context) const override;

  protected:
    void defineType(lang::ResolvingHandle<lang::Type> type) override;

  public:
    ~Or() override;

  private:
    bool              negate_;
    Owned<Expression> left_;
    Owned<Expression> right_;
};

#endif
