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
     * @param left The left operand.
     * @param right The right operand.
     * @param location The source location of the operation.
     */
    And(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right, lang::Location location);

    [[nodiscard]] Expression& left() const;
    [[nodiscard]] Expression& right() const;

  public:
    [[nodiscard]] std::optional<lang::ResolvingHandle<lang::Type>> tryGetType() const override;

    bool validate(ValidationLogger& validation_logger) const override;

    [[nodiscard]] Expansion expandWith(Expressions subexpressions) const override;

  public:
    ~And() override;

  private:
    std::unique_ptr<Expression> left_;
    std::unique_ptr<Expression> right_;
};

#endif
