#ifndef ANCE_SRC_ANCE_STATEMENT_ASSIGNMENTSTATEMENT_H_
#define ANCE_SRC_ANCE_STATEMENT_ASSIGNMENTSTATEMENT_H_

#include "Statement.h"

#include "lang/Assigner.h"
#include "lang/Assigner.h"

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
    AssignmentStatement(std::unique_ptr<Expression> assignable,
                        lang::Assigner              assigner,
                        std::unique_ptr<Expression> assigned,
                        lang::Location              location);

    void setFunction(lang::Function* function) override;

    void validate(ValidationLogger& validation_logger) override;

  protected:
    void doBuild(CompileContext* context) override;

  private:
    std::unique_ptr<Expression> assignable_;
    lang::Assigner              assigner_;
    std::unique_ptr<Expression> assigned_;
};
#endif