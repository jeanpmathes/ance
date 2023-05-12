#ifndef ANCE_SRC_LANG_STATEMENT_RETURN_H_
#define ANCE_SRC_LANG_STATEMENT_RETURN_H_

#include "Statement.h"

#include <optional>

#include "lang/Element.h"

class Expression;

/**
 * Returns from the containing function.
 */
class Return
    : public Statement
    , public lang::Element<Return, ANCE_CONSTRUCTS>
{
  public:
    /**
     * Create a return statement.
     * @param return_value An expression producing the return value.
     * @param location The source location.
     */
    Return(Optional<Owned<Expression>> return_value, lang::Location location);

    [[nodiscard]] Expression const* expression() const;

    std::vector<Owned<lang::BasicBlock>> createBasicBlocks(lang::BasicBlock& entry, lang::Function& function) override;

    void validate(ValidationLogger& validation_logger) const override;

  protected:
    [[nodiscard]] Statements expandWith(Expressions    subexpressions,
                                        Statements     substatements,
                                        lang::Context& new_context) const override;

    [[nodiscard]] Statements arrangeExpandedStatements(Statements before,
                                                       Statements expanded,
                                                       Statements after) const override;

    void doBuild(CompileContext& context) override;

  private:
    Optional<Owned<Expression>> return_value_;
};

#endif
