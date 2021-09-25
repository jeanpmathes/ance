#ifndef ANCE_SRC_ANCE_STATEMENT_RETURNSTATEMENT_H_
#define ANCE_SRC_ANCE_STATEMENT_RETURNSTATEMENT_H_

#include "Statement.h"

class Expression;

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

    void validate(ValidationLogger& validation_logger) override;

    bool accept(ance::ApplicationVisitor& visitor) override;

  protected:
    void doBuild(CompileContext* context) override;

  private:
    Expression* return_value_;
};
#endif