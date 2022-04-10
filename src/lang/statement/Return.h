#ifndef ANCE_SRC_LANG_STATEMENT_RETURN_H_
#define ANCE_SRC_LANG_STATEMENT_RETURN_H_

#include "Statement.h"

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
    Return(std::unique_ptr<Expression> return_value, lang::Location location);

    [[nodiscard]] Expression* expression();

    std::vector<std::unique_ptr<lang::BasicBlock>> createBlocks(lang::BasicBlock& entry,
                                                                lang::Function*   function) override;

    void validate(ValidationLogger& validation_logger) override;

  protected:
    void doBuild(CompileContext* context) override;

  private:
    std::unique_ptr<Expression> return_value_;
};

#endif