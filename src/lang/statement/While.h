#ifndef ANCE_SRC_LANG_STATEMENT_WHILE_H_
#define ANCE_SRC_LANG_STATEMENT_WHILE_H_

#include "Statement.h"

#include <memory>

#include "lang/Element.h"

class Expression;

/**
 * A while control flow statement.
 */
class While
    : public Statement
    , public lang::Element<While, ANCE_CONSTRUCTS>
{
  public:
    /**
     * Create a new while-statement.
     * @param condition The condition to check.
     * @param block The block to execute if the condition is true.
     * @param location The source location of the statement.
     */
    While(Owned<Expression> condition, Owned<Statement> block, lang::Location location);

    [[nodiscard]] Expression const& condition() const;
    [[nodiscard]] Statement const&  body() const;

    std::vector<Owned<lang::BasicBlock>> createBasicBlocks(lang::BasicBlock& entry, lang::Function& function) override;

    void validate(ValidationLogger& validation_logger) const override;

    [[nodiscard]] Statements expandWith(Expressions    subexpressions,
                                        Statements     substatements,
                                        lang::Context& new_context) const override;

  protected:
    Statements arrangeExpandedStatements(Statements before, Statements expanded, Statements after) const override;

    [[nodiscard]] bool                                            isLoop() const override;
    [[nodiscard]] std::pair<lang::BasicBlock*, lang::BasicBlock*> getLoopParts() const override;

  private:
    std::pair<lang::BasicBlock*, lang::BasicBlock*> loop_parts_ {nullptr, nullptr};

    Owned<Expression> condition_;
    Owned<Statement>  block_;
};

#endif
