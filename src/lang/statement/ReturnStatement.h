#ifndef ANCE_SRC_LANG_STATEMENT_RETURNSTATEMENT_H_
#define ANCE_SRC_LANG_STATEMENT_RETURNSTATEMENT_H_

#include "Statement.h"

#include "lang/Element.h"

class Expression;

/**
 * Adds a return value to the containing function.
 */
class ReturnStatement
    : public Statement
    , public lang::Element<ReturnStatement, ANCE_CONSTRUCTS>
{
  public:
    /**
     * Create a return statement.
     * @param return_value An expression producing the return value.
     * @param location The source location.
     */
    ReturnStatement(std::unique_ptr<Expression> return_value, lang::Location location);

    [[nodiscard]] Expression* expression();

    std::unique_ptr<lang::BasicBlock> createBlock() override;

    void setScope(lang::Scope* scope) override;
    void walkDefinitions() override;

    void validate(ValidationLogger& validation_logger) override;

  protected:
    void doBuild(CompileContext* context) override;

  private:
    std::unique_ptr<Expression> return_value_;
};
#endif