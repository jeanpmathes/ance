#ifndef ANCE_SRC_LANG_STATEMENT_CONTINUE_H_
#define ANCE_SRC_LANG_STATEMENT_CONTINUE_H_

#include "Statement.h"

#include "lang/Element.h"

class Expression;

/**
 * A statement to continue a loop.
 */
class Continue
    : public Statement
    , public lang::Element<Continue, ANCE_CONSTRUCTS>
{
  public:
    /**
     * Create a new continue statement.
     * @param location The source location.
     */
    explicit Continue(lang::Location location);

    void validate(ValidationLogger& validation_logger) const override;

    std::vector<Owned<lang::BasicBlock>> createBasicBlocks(lang::BasicBlock& entry, lang::Function& function) override;

    [[nodiscard]] Statements expandWith(Expressions    subexpressions,
                                        Statements     substatements,
                                        lang::Context& new_context) const override;

  protected:
    void doBuild(CompileContext& context) override;

  private:
    [[nodiscard]] Statement const* getLoopParent() const;
};

#endif
