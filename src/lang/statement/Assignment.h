#ifndef ANCE_SRC_LANG_STATEMENT_ASSIGNMENT_H_
#define ANCE_SRC_LANG_STATEMENT_ASSIGNMENT_H_

#include "Statement.h"

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
    Assignment(Owned<Expression> assignable,
               lang::Assigner    assigner,
               Owned<Expression> assigned,
               lang::Location    location);

    [[nodiscard]] Expression const& assignable() const;
    [[nodiscard]] lang::Assigner    assigner() const;
    [[nodiscard]] Expression const& assigned() const;

    void validate(ValidationLogger& validation_logger) const override;

    [[nodiscard]] Statements expandWith(Expressions subexpressions, Statements substatements) const override;

  protected:
    void doBuild(CompileContext& context) override;

  private:
    Owned<Expression> assignable_;
    lang::Assigner    assigner_;
    Owned<Expression> assigned_;
};
#endif
