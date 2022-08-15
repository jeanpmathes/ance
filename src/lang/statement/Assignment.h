#ifndef ANCE_SRC_LANG_STATEMENT_ASSIGNMENT_H_
#define ANCE_SRC_LANG_STATEMENT_ASSIGNMENT_H_

#include "Statement.h"

#include "lang/Assigner.h"
#include "lang/Assigner.h"

#include "lang/Element.h"

class Expression;

/**
 * A statement with an assignment operation.
 */
class Assignment
    : public Statement
    , public lang::Element<Assignment, ANCE_CONSTRUCTS>
{
  public:
    /**
     * Create a new assignment statement.
     * @param assignable The assignable that is assigned too.
     * @param assigner The used assigner.
     * @param assigned An expression producing the value that is assigned.
     * @param location The source location.
     */
    Assignment(std::unique_ptr<Expression> assignable,
               lang::Assigner              assigner,
               std::unique_ptr<Expression> assigned,
               lang::Location              location);

    [[nodiscard]] Expression&    assignable() const;
    [[nodiscard]] lang::Assigner assigner() const;
    [[nodiscard]] Expression&    assigned() const;

    void validate(ValidationLogger& validation_logger) const override;

    Statements expandWith(Expressions subexpressions, Statements substatements) const override;

  protected:
    void doBuild(CompileContext& context) override;

  private:
    std::unique_ptr<Expression> assignable_;
    lang::Assigner              assigner_;
    std::unique_ptr<Expression> assigned_;
};
#endif