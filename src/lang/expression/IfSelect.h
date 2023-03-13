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
    IfSelect(Owned<Expression> condition,
             Owned<Expression> then_expression,
             Owned<Expression> else_expression,
             lang::Location    location);

    [[nodiscard]] Expression const& condition() const;
    [[nodiscard]] Expression const& thenExpression() const;
    [[nodiscard]] Expression const& elseExpression() const;

  public:
    bool validate(ValidationLogger& validation_logger) const override;

    [[nodiscard]] Expansion expandWith(Expressions subexpressions, lang::Context& new_context) const override;

  protected:
    void defineType(lang::ResolvingHandle<lang::Type> type) override;

  public:
    ~IfSelect() override;

  private:
    Owned<Expression> condition_;
    Owned<Expression> then_expression_;
    Owned<Expression> else_expression_;
};

#endif
