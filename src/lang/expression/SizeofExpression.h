#ifndef ANCE_SRC_LANG_EXPRESSION_SIZEOFEXPRESSION_H_
#define ANCE_SRC_LANG_EXPRESSION_SIZEOFEXPRESSION_H_

#include "Expression.h"

#include "lang/Element.h"

class Application;

/**
 * Gives the size of a value returned by an expression.
 */
class SizeofExpression
    : public Expression
    , public lang::Element<SizeofExpression, ANCE_CONSTRUCTS>
{
  public:
    /**
     * Create a new sizeof expression expression.
     * @param expression The expression to get the size of.
     * @param location The source location.
     */
    SizeofExpression(Owned<Expression> expression, lang::Location location);

    [[nodiscard]] Expression const& expression() const;

    bool validate(ValidationLogger& validation_logger) const override;

    [[nodiscard]] Expansion expandWith(Expressions subexpressions, lang::Context& new_context) const override;

  protected:
    void defineType(lang::ResolvingHandle<lang::Type> type) override;

  private:
    Owned<Expression> expression_;
};

#endif
