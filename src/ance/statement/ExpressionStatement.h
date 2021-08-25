#ifndef ANCE_SRC_ANCE_STATEMENT_EXPRESSIONSTATEMENT_H_
#define ANCE_SRC_ANCE_STATEMENT_EXPRESSIONSTATEMENT_H_

#include "Statement.h"

class BuildableExpression;

/**
 * A statement that consists of an expression.
 */
class ExpressionStatement : public Statement
{
  public:
    /**
     * Create a new expression statement.
     * @param expression The expression to use for this statement.
     * @param location The source location.
     */
    ExpressionStatement(BuildableExpression* expression, ance::Location location);

    void setFunction(ance::DefinedFunction* function) override;

  protected:
    void doBuild(CompileContext* context) override;

  private:
    BuildableExpression* expression_;
};
#endif