#ifndef ANCE_SRC_LANG_STATEMENT_EXPRESSIONSTATEMENT_H_
#define ANCE_SRC_LANG_STATEMENT_EXPRESSIONSTATEMENT_H_

#include "CompileTimeStatement.h"

#include "lang/Element.h"

/**
 * A statement that consists of an expression.
 */
class ExpressionStatement
    : public CompileTimeStatement
    , public lang::Element<ExpressionStatement, ANCE_CONSTRUCTS>
{
  public:
    /**
     * Create a new expression statement.
     * @param expression The expression to use for this statement.
     * @param location The source location.
     */
    ExpressionStatement(Owned<Expression> expression, lang::Location location);

    [[nodiscard]] Expression const& expression() const;

    bool validate(ValidationLogger& validation_logger) const override;

    [[nodiscard]] Statements expandWith(Expressions    subexpressions,
                                        Statements     substatements,
                                        lang::Context& new_context) const override;

  private:
    Owned<Expression> expression_;
};
#endif
