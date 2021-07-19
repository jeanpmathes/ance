#ifndef ANCE_SRC_ANCE_STATEMENT_RETURNSTATEMENT_H_
#define ANCE_SRC_ANCE_STATEMENT_RETURNSTATEMENT_H_

#include "Statement.h"

#include "ance/expression/Expression.h"

class ReturnStatement : public Statement
{
  public:
    ReturnStatement(Expression* return_value, unsigned int line, unsigned int column);

    void setFunction(ance::DefinedFunction* function) override;

    void build(CompileContext* context) override;

  private:
    Expression* return_value_;
};
#endif