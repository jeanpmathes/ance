#ifndef ANCE_SRC_LANG_STATEMENT_LOCALREFERENCEVARIABLEDEFINITION_H_
#define ANCE_SRC_LANG_STATEMENT_LOCALREFERENCEVARIABLEDEFINITION_H_

#include "Statement.h"

#include <optional>

#include "lang/Assigner.h"
#include "lang/Element.h"
#include "lang/construct/Variable.h"
#include "lang/utility/ResolvingHandle.h"

namespace lang
{
    class Type;
}

class Expression;
class Application;

/**
 * Defines a local variable of reference type in the containing function.
 */
class LocalReferenceVariableDefinition
    : public Statement
    , public lang::Element<LocalReferenceVariableDefinition, ANCE_CONSTRUCTS>
{
  public:
    /**
     * Constructs a new local reference variable definition.
     * @param name The name of the variable.
     * @param type The type of the variable.
     * @param type_location The location of the type.
     * @param reference The reference to bind.
     * @param location The location of the local reference variable definition.
     */
    LocalReferenceVariableDefinition(lang::Identifier                  name,
                                     lang::ResolvingHandle<lang::Type> type,
                                     lang::Location                    type_location,
                                     std::unique_ptr<Expression>       reference,
                                     lang::Location                    location);

  public:
    [[nodiscard]] lang::Identifier const&           name() const;
    [[nodiscard]] lang::ResolvingHandle<lang::Type> type() const;
    [[nodiscard]] Expression&                       reference() const;

  public:
    void setScope(lang::Scope& scope) override;
    void walkDefinitions() override;

    void validate(ValidationLogger& validation_logger) const override;

    Statements expandWith(Expressions subexpressions, Statements substatements) const override;

  protected:
    void doBuild(CompileContext& context) override;

  private:
    lang::Identifier                  name_;
    lang::ResolvingHandle<lang::Type> type_;
    lang::Location                    type_location_;
    std::unique_ptr<Expression>       reference_;

    std::optional<lang::ResolvingHandle<lang::Variable>> variable_ {};
};

#endif
