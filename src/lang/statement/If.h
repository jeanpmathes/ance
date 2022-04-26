#ifndef ANCE_SRC_LANG_STATEMENT_IF_H_
#define ANCE_SRC_LANG_STATEMENT_IF_H_

#include "Statement.h"

#include "lang/Element.h"

class Expression;

/**
 * An if-else control flow statement.
 */
class If
    : public Statement
    , public lang::Element<If, ANCE_CONSTRUCTS>
{
  public:
    /**
     * Create a new if-else statement.
     * @param condition The condition to evaluate.
     * @param if_block The block to execute if the condition is true.
     * @param else_block The block to execute if the condition is false. May be null.
     * @param location The location of the statement.
     */
    If(std::unique_ptr<Expression> condition,
       std::unique_ptr<Statement>  if_block,
       std::unique_ptr<Statement>  else_block,
       lang::Location              location);

    [[nodiscard]] Expression& condition();

    std::vector<std::unique_ptr<lang::BasicBlock>> createBasicBlocks(lang::BasicBlock& entry,
                                                                     lang::Function*   function) override;

    void validate(ValidationLogger& validation_logger) override;

    Statements expandWith(Expressions subexpressions, Statements substatements) const override;

  protected:
    void doBuild(CompileContext* context) override;

  private:
    std::unique_ptr<Expression> condition_;

    std::unique_ptr<Statement> if_block_;
    std::unique_ptr<Statement> else_block_;
};

#endif
