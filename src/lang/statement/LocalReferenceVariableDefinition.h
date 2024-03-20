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
                                     Owned<Expression>                 reference,
                                     lang::Location                    location);

  public:
    [[nodiscard]] lang::Identifier const& name() const;
    [[nodiscard]] lang::Type const&       type() const;
    [[nodiscard]] Expression const&       reference() const;
    [[nodiscard]] lang::Variable const&   variable() const;

  public:
    void setScope(lang::Scope& scope) override;
    void walkDefinitions() override;

    void validate(ValidationLogger& validation_logger) const override;

    [[nodiscard]] Statements expandWith(Expressions    subexpressions,
                                        Statements     substatements,
                                        lang::Context& new_context) const override;

  private:
    lang::Identifier                    name_;
    lang::ResolvingHandle<lang::Entity> type_;
    lang::Location                      type_location_;
    Owned<Expression>                   reference_;

    Optional<lang::ResolvingHandle<lang::Variable>> variable_ {};
};

#endif
