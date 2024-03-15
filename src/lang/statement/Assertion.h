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
    Assertion(Owned<Expression> condition, lang::Location location);

    [[nodiscard]] Expression const& condition() const;

    void validate(ValidationLogger& validation_logger) const override;

    [[nodiscard]] Statements expandWith(Expressions    subexpressions,
                                        Statements     substatements,
                                        lang::Context& new_context) const override;

  private:
    Owned<Expression> condition_;
};

#endif
