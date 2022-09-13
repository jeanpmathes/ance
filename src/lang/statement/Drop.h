#ifndef ANCE_SRC_LANG_STATEMENT_DROP_H_
#define ANCE_SRC_LANG_STATEMENT_DROP_H_

#include "Statement.h"

#include "lang/Element.h"
#include "lang/construct/Variable.h"
#include "lang/utility/ResolvingHandle.h"

class Expression;

/**
 * The drop statement drops a defined variable.
 */
class Drop
    : public Statement
    , public lang::Element<Drop, ANCE_CONSTRUCTS>
{
  public:
    /**
     * Creates a new drop statement.
     * @param variable The the variable to drop.
     * @param location The location of the statement.
     */
    Drop(lang::ResolvingHandle<lang::Variable> variable, lang::Location location);

    [[nodiscard]] lang::ResolvingHandle<lang::Variable> variable() const;

    void walkDefinitions() override;

    void validate(ValidationLogger& validation_logger) const override;

    Statements expandWith(Expressions subexpressions, Statements substatements) const override;

  protected:
    void doBuild(CompileContext& context) override;

  private:
    lang::ResolvingHandle<lang::Variable> variable_;
    bool                                  dropped_;
};
#endif

