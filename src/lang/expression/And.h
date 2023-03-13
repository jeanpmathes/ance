#ifndef ANCE_SRC_LANG_EXPRESSION_AND_H_
#define ANCE_SRC_LANG_EXPRESSION_AND_H_

#include "UnexpandedExpression.h"

#include "lang/Element.h"

/**
 * Logical 'and' expression, with short-circuit evaluation.
 */
class And
    : public UnexpandedExpression
    , public lang::Element<And, ANCE_CONSTRUCTS>
{
  public:
    /**
     * Create a new logical 'and' expression.
     * @param negate Whether to negate the result.
     * @param left The left operand.
     * @param right The right operand.
     * @param location The source location of the operation.
     */
    And(bool negate, Owned<Expression> left, Owned<Expression> right, lang::Location location);

    [[nodiscard]] bool              negate() const;
    [[nodiscard]] Expression const& left() const;
    [[nodiscard]] Expression const& right() const;

  public:
    bool validate(ValidationLogger& validation_logger) const override;

    [[nodiscard]] Expansion expandWith(Expressions subexpressions, lang::Context& new_context) const override;

  protected:
    void defineType(lang::ResolvingHandle<lang::Type> type) override;

  public:
    ~And() override;

  private:
    bool              negate_;
    Owned<Expression> left_;
    Owned<Expression> right_;
};

#endif
