#ifndef ANCE_SRC_ANCE_STATEMENT_RETURNSTATEMENT_H_
#define ANCE_SRC_ANCE_STATEMENT_RETURNSTATEMENT_H_

#include "Statement.h"

#include "ance/expression/Expression.h"

/**
 * Adds a return value to the containing function.
 */
class ReturnStatement : public Statement
{
  public:
    /**
     * Create a return statement.
     * @param return_value An expression producing the return value.
     * @param location The source location.
     */
    ReturnStatement(Expression* return_value, ance::Location location);

    void setFunction(ance::DefinedFunction* function) override;

    void build(CompileContext* context) override;

  private:
    Expression* return_value_;
};
#endif