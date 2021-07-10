#ifndef ANCE_SRC_ANCE_STATEMENT_DELETESTATEMENT_H_
#define ANCE_SRC_ANCE_STATEMENT_DELETESTATEMENT_H_

#include "Expression.h"
#include "Statement.h"

class DeleteStatement : public Statement
{
  public:
    DeleteStatement(Expression* to_delete, bool delete_buffer, unsigned int l, unsigned int c);

    void setContainingFunction(ance::DefinedFunction* function) override;

    void build(CompileContext* context) override;

  private:
    Expression* to_delete_;
    bool        delete_buffer_;
};

#endif
