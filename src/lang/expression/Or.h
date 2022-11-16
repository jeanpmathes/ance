#ifndef ANCE_SRC_LANG_EXPRESSION_OR_H_
#define ANCE_SRC_LANG_EXPRESSION_OR_H_

#include "UnexpandedExpression.h"

#include "lang/Element.h"

/**
 * Logical 'or' expression, with short-circuit evaluation.
 */
class Or
    : public UnexpandedExpression
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
    Or(bool negate, std::unique_ptr<Expression> left, std::unique_ptr<Expression> right, lang::Location location);

    [[nodiscard]] bool        negate() const;
    [[nodiscard]] Expression& left() const;
    [[nodiscard]] Expression& right() const;

  public:
    [[nodiscard]] std::optional<lang::ResolvingHandle<lang::Type>> tryGetType() const override;

    bool validate(ValidationLogger& validation_logger) const override;

    [[nodiscard]] Expansion expandWith(Expressions subexpressions) const override;

  public:
    ~Or() override;

  private:
    bool                        negate_;
    std::unique_ptr<Expression> left_;
    std::unique_ptr<Expression> right_;
};

#endif
