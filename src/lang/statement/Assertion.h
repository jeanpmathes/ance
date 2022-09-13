#ifndef ANCE_SRC_LANG_STATEMENT_ASSERTION_H_
#define ANCE_SRC_LANG_STATEMENT_ASSERTION_H_

#include "Statement.h"

#include "lang/Element.h"

class Expression;

/**
 * A statement that asserts a condition.
 */
class Assertion
    : public Statement
    , public lang::Element<Assertion, ANCE_CONSTRUCTS>
{
  public:
    /**
     * Create a new assertion.
     * @param condition The condition to assert.
     * @param location The location of the statement.
     */
    Assertion(std::unique_ptr<Expression> condition, lang::Location location);

    [[nodiscard]] Expression& condition() const;

    void validate(ValidationLogger& validation_logger) const override;

    Statements expandWith(Expressions subexpressions, Statements substatements) const override;

  protected:
    void doBuild(CompileContext& context) override;

  private:
    std::unique_ptr<Expression> condition_;
};

#endif

