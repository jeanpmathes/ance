#ifndef ANCE_SRC_LANG_STATEMENT_IF_H_
#define ANCE_SRC_LANG_STATEMENT_IF_H_

#include "CompileTimeStatement.h"

#include "lang/Element.h"

#include "lang/utility/Owners.h"

class Expression;

/**
 * An if-else control flow statement.
 */
class If
    : public CompileTimeStatement
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
    If(Owned<Expression>          condition,
       Owned<Statement>           if_block,
       Optional<Owned<Statement>> else_block,
       lang::Location             location);

    [[nodiscard]] Expression const& condition() const;
    [[nodiscard]] Statement const*  ifBlock() const;
    [[nodiscard]] Statement const*  elseBlock() const;

    std::vector<Owned<lang::BasicBlock>> createBasicBlocks(lang::BasicBlock& entry, lang::Function& function) override;

    bool validate(ValidationLogger& validation_logger) const override;

    [[nodiscard]] Statements expandWith(Expressions    subexpressions,
                                        Statements     substatements,
                                        lang::Context& new_context) const override;

  private:
    Owned<Expression> condition_;

    Optional<Owned<Statement>> if_block_;
    Optional<Owned<Statement>> else_block_;
};

#endif
