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
    ReturnStatement(std::unique_ptr<Expression> return_value, lang::Location location);

    void setFunction(lang::Function* function) override;

    void validate(ValidationLogger& validation_logger) override;

  protected:
    void doBuild(CompileContext* context) override;

  private:
    std::unique_ptr<Expression> return_value_;
};
#endif