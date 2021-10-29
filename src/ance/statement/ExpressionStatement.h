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
    ExpressionStatement(std::unique_ptr<BuildableExpression> expression, ance::Location location);

    void setFunction(ance::Function* function) override;

    void validate(ValidationLogger& validation_logger) override;

  protected:
    void doBuild(CompileContext* context) override;

  private:
    std::unique_ptr<BuildableExpression> expression_;
};
#endif