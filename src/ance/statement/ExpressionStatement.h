#ifndef ANCE_SRC_ANCE_STATEMENT_EXPRESSIONSTATEMENT_H_
#define ANCE_SRC_ANCE_STATEMENT_EXPRESSIONSTATEMENT_H_

#include "Statement.h"

class BuildableExpression;

class ExpressionStatement : public Statement
{
  public:
    ExpressionStatement(BuildableExpression* expression, ance::Location location);

    void setFunction(ance::DefinedFunction* function) override;

    void build(CompileContext* context) override;

  private:
    BuildableExpression* expression_;
};
#endif