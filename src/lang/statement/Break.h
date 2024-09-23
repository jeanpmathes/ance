#ifndef ANCE_SRC_LANG_STATEMENT_BREAK_H_
#define ANCE_SRC_LANG_STATEMENT_BREAK_H_

#include "Statement.h"

#include "lang/Element.h"

class Expression;

/**
 * A statement to break a loop.
 */
class Break
    : public Statement
    , public lang::Element<Break, ANCE_CONSTRUCTS>
{
  public:
    /**
     * Create a new break statement.
     * @param location The source location.
     */
    explicit Break(lang::Location location);

    bool validate(ValidationLogger& validation_logger) const override;

    std::vector<Owned<lang::BasicBlock>> createBasicBlocks(lang::BasicBlock& entry, lang::Function& function) override;

    [[nodiscard]] Statements expandWith(Expressions    subexpressions,
                                        Statements     substatements,
                                        lang::Context& new_context) const override;

  private:
    [[nodiscard]] Statement const* getLoopParent() const;
};

#endif
