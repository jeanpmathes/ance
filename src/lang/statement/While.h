#ifndef ANCE_SRC_LANG_STATEMENT_WHILE_H_
#define ANCE_SRC_LANG_STATEMENT_WHILE_H_

#include "Statement.h"

#include <memory>

#include "lang/Element.h"

class Expression;

/**
 * An if-else control flow statement.
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
    While(std::unique_ptr<Expression> condition, std::unique_ptr<Statement> block, lang::Location location);

    [[nodiscard]] Expression& condition();
    [[nodiscard]] Statement&  body();

    std::vector<std::unique_ptr<lang::BasicBlock>> createBasicBlocks(lang::BasicBlock& entry,
                                                                     lang::Function&   function) override;

    void validate(ValidationLogger& validation_logger) const override;

    Statements expandWith(Expressions subexpressions, Statements substatements) const override;

  protected:
    void doBuild(CompileContext& context) override;

    [[nodiscard]] bool                                            isLoop() const override;
    [[nodiscard]] std::pair<lang::BasicBlock*, lang::BasicBlock*> getLoopParts() const override;

  private:
    std::pair<lang::BasicBlock*, lang::BasicBlock*> loop_parts_ {nullptr, nullptr};

    std::unique_ptr<Expression> condition_;
    std::unique_ptr<Statement>  block_;
};

#endif
