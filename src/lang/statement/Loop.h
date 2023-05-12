#ifndef ANCE_SRC_LANG_STATEMENT_LOOP_H_
#define ANCE_SRC_LANG_STATEMENT_LOOP_H_

#include "Statement.h"

#include <memory>

#include "lang/Element.h"

class Expression;

/**
 * A loop control flow statement.
 */
class Loop
    : public Statement
    , public lang::Element<Loop, ANCE_CONSTRUCTS>
{
  public:
    /**
     * Create a new loop-statement.
     * @param block The block to execute if the condition is true.
     * @param location The source location of the statement.
     */
    Loop(Owned<Statement> block, lang::Location location);

    [[nodiscard]] Statement const& body() const;

    std::vector<Owned<lang::BasicBlock>> createBasicBlocks(lang::BasicBlock& entry, lang::Function& function) override;

    void validate(ValidationLogger& validation_logger) const override;

    [[nodiscard]] Statements expandWith(Expressions    subexpressions,
                                        Statements     substatements,
                                        lang::Context& new_context) const override;

  protected:
    void doBuild(CompileContext& context) override;

    [[nodiscard]] bool                                            isLoop() const override;
    [[nodiscard]] std::pair<lang::BasicBlock*, lang::BasicBlock*> getLoopParts() const override;

  private:
    std::pair<lang::BasicBlock*, lang::BasicBlock*> loop_parts_ {nullptr, nullptr};

    Owned<Statement> block_;
};
#endif
