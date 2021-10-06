#ifndef ANCE_SRC_ANCE_STATEMENT_ASSIGNMENTSTATEMENT_H_
#define ANCE_SRC_ANCE_STATEMENT_ASSIGNMENTSTATEMENT_H_

#include "Statement.h"

#include "ance/Assigner.h"

class Expression;

/**
 * A statement with an assignment operation.
 */
class AssignmentStatement : public Statement
{
  public:
    /**
     * Create a new assignment statement.
     * @param assignable The assignable that is assigned too.
     * @param assigner The used assigner.
     * @param assigned An expression producing the value that is assigned.
     * @param location The source location.
     */
    AssignmentStatement(Expression* assignable, Assigner assigner, Expression* assigned, ance::Location location);

    void setFunction(ance::DefinedFunction* function) override;

    void validate(ValidationLogger& validation_logger) override;

    bool accept(ance::ApplicationVisitor& visitor) override;

  protected:
    void doBuild(CompileContext* context) override;

  private:
    Expression* assignable_;
    Assigner    assigner_;
    Expression* assigned_;
};
#endif