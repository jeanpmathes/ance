#ifndef ANCE_SRC_ANCE_STATEMENT_DELETESTATEMENT_H_
#define ANCE_SRC_ANCE_STATEMENT_DELETESTATEMENT_H_

#include "Statement.h"

#include "ance/expression/Expression.h"

class DeleteStatement : public Statement
{
  public:
    DeleteStatement(Expression* to_delete, bool delete_buffer, ance::Location location);

    void setFunction(ance::DefinedFunction* function) override;

    void build(CompileContext* context) override;

  private:
    Expression* to_delete_;
    bool        delete_buffer_;
};

#endif
