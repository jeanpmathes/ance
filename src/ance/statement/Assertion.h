#ifndef ANCE_SRC_ANCE_STATEMENT_ASSERTION_H_
#define ANCE_SRC_ANCE_STATEMENT_ASSERTION_H_

#include "Statement.h"

class Expression;

/**
 * A statement that asserts a condition.
 */
class Assertion : public Statement
{
  public:
    /**
     * Create a new assertion.
     * @param condition The condition to assert.
     * @param location The location of the statement.
     */
    Assertion(std::unique_ptr<Expression> condition, ance::Location location);

    void setFunction(ance::Function* function) override;

    void validate(ValidationLogger& validation_logger) override;

  protected:
    void doBuild(CompileContext* context) override;

  private:
    std::unique_ptr<Expression> condition_;
};

#endif