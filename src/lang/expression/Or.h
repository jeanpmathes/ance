#ifndef ANCE_SRC_LANG_EXPRESSION_OR_H_
#define ANCE_SRC_LANG_EXPRESSION_OR_H_

#include "DelayableExpression.h"

#include "lang/Element.h"

/**
 * Logical 'or' expression, with short-circuit evaluation.
 */
class Or
    : public DelayableExpression
    , public lang::Element<Or, ANCE_CONSTRUCTS>
{
  public:
    /**
     * Create a new logical 'or' expression.
     * @param left The left operand.
     * @param right The right operand.
     * @param location The source location of the operation.
     */
    Or(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right, lang::Location location);

    [[nodiscard]] Expression& left() const;
    [[nodiscard]] Expression& right() const;

  public:
    lang::ResolvingHandle<lang::Type> type() override;

    bool validate(ValidationLogger& validation_logger) override;

    [[nodiscard]] Expansion expandWith(Expressions subexpressions) const override;

  protected:
    void doBuild(CompileContext* context) override;

  public:
    ~Or() override;

  private:
    std::unique_ptr<Expression> left_;
    std::unique_ptr<Expression> right_;
};

#endif
