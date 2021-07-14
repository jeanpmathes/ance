#ifndef ANCE_SRC_ANCE_STATEMENT_RETURNSTATEMENT_H_
#define ANCE_SRC_ANCE_STATEMENT_RETURNSTATEMENT_H_

#include "Expression.h"
#include "Statement.h"

class ReturnStatement : public Statement
{
  public:
    ReturnStatement(Expression* return_value, unsigned int l, unsigned int c);

    void setContainingFunction(ance::DefinedFunction* function) override;

    void build(CompileContext* context) override;

  private:
    Expression* return_value_;
};
#endif