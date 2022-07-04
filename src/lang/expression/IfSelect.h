#ifndef ANCE_SRC_LANG_EXPRESSION_IFSELECT_H_
#define ANCE_SRC_LANG_EXPRESSION_IFSELECT_H_

#include "UnexpandedExpression.h"

#include <memory>

#include "lang/Element.h"

/**
 * An if-expression that selects between two expressions. Similar to the ternary operator.
 */
class IfSelect
    : public UnexpandedExpression
    , public lang::Element<IfSelect, ANCE_CONSTRUCTS>
{
  public:
    /**
     * Creates a new if-expression.
     * @param condition The condition to evaluate.
     * @param then_expression The expression to evaluate if the condition is true.
     * @param else_expression The expression to evaluate if the condition is false.
     * @param location The location of the expression.
     */
    IfSelect(std::unique_ptr<Expression> condition,
             std::unique_ptr<Expression> then_expression,
             std::unique_ptr<Expression> else_expression,
             lang::Location              location);

    [[nodiscard]] Expression& condition() const;
    [[nodiscard]] Expression& thenExpression() const;
    [[nodiscard]] Expression& elseExpression() const;

  public:
    lang::ResolvingHandle<lang::Type> type() const override;

    bool validate(ValidationLogger& validation_logger) const override;

    [[nodiscard]] Expansion expandWith(Expressions subexpressions) const override;

  public:
    ~IfSelect() override;

  private:
    std::unique_ptr<Expression> condition_;
    std::unique_ptr<Expression> then_expression_;
    std::unique_ptr<Expression> else_expression_;
};

#endif
