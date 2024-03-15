#ifndef ANCE_SRC_LANG_STATEMENT_ERASE_H_
#define ANCE_SRC_LANG_STATEMENT_ERASE_H_

#include "Statement.h"

#include "lang/Element.h"
#include "lang/construct/Variable.h"
#include "lang/utility/ResolvingHandle.h"

class Expression;

/**
 * The erase statement removes a defined variable.
 */
class Erase
    : public Statement
    , public lang::Element<Erase, ANCE_CONSTRUCTS>
{
  public:
    /**
     * Creates a new erase statement.
     * @param variable The the variable to erase.
     * @param location The location of the statement.
     */
    Erase(lang::ResolvingHandle<lang::Variable> variable, lang::Location location);

    [[nodiscard]] lang::ResolvingHandle<lang::Entity> variable();
    [[nodiscard]] lang::Entity const&                 variable() const;

    void walkDefinitions() override;

    void validate(ValidationLogger& validation_logger) const override;

    Statements expandWith(Expressions    subexpressions,
                          Statements     substatements,
                          lang::Context& new_context) const override;

  private:
    lang::ResolvingHandle<lang::Entity> variable_;
    bool                                erased_;
};
#endif
