#ifndef ANCE_SRC_LANG_STATEMENT_EXPRESSIONSTATEMENT_H_
#define ANCE_SRC_LANG_STATEMENT_EXPRESSIONSTATEMENT_H_

#include "Statement.h"

#include "lang/Element.h"

class BuildableExpression;

/**
 * A statement that consists of an expression.
 */
class ExpressionStatement
    : public Statement
    , public lang::Element<ExpressionStatement, ANCE_CONSTRUCTS>
{
  public:
    /**
     * Create a new expression statement.
     * @param expression The expression to use for this statement.
     * @param location The source location.
     */
    ExpressionStatement(Owned<BuildableExpression> expression, lang::Location location);

    [[nodiscard]] BuildableExpression const& expression() const;

    void validate(ValidationLogger& validation_logger) const override;

    [[nodiscard]] Statements expandWith(Expressions subexpressions, Statements substatements) const override;

  protected:
    void doBuild(CompileContext& context) override;

  private:
    Owned<BuildableExpression> expression_;
};
#endif
