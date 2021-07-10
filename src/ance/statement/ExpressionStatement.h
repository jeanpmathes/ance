#pragma once

#include "Statement.h"

class BuildableExpression;

class ExpressionStatement : public Statement
{
  public:
    ExpressionStatement(BuildableExpression* expression, unsigned int l, unsigned int c);

    void setContainingFunction(ance::DefinedFunction* function) override;

    void build(CompileContext* context) override;

  private:
    BuildableExpression* expression_;
};
