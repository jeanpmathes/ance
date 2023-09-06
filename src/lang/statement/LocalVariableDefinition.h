#ifndef ANCE_SRC_LANG_STATEMENT_LOCALVARIABLEDEFINITION_H_
#define ANCE_SRC_LANG_STATEMENT_LOCALVARIABLEDEFINITION_H_

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

/**
 * Defines a local variable in the containing function.
 */
class LocalVariableDefinition
    : public Statement
    , public lang::Element<LocalVariableDefinition, ANCE_CONSTRUCTS>
{
  public:
    /**
     * Create a new local variable definition.
     * @param name The name of the variable.
     * @param type The type of the variable.
     * @param type_location The location of the type.
     * @param assigner The assigner to use for initial assignment.
     * @param assigned The initially assigned value, or nullptr if a default value is used.
     * @param location The source location.
     */
    LocalVariableDefinition(lang::Identifier                            name,
                            Optional<lang::ResolvingHandle<lang::Type>> type,
                            lang::Location                              type_location,
                            lang::Assigner                              assigner,
                            Optional<Owned<Expression>>                 assigned,
                            lang::Location                              location);

    [[nodiscard]] lang::Identifier const& name() const;
    [[nodiscard]] lang::Type const*       type() const;
    [[nodiscard]] lang::Assigner          assigner() const;
    [[nodiscard]] Expression const*       assigned() const;

    void setScope(lang::Scope& scope) override;
    void walkDefinitions() override;

    void validate(ValidationLogger& validation_logger) const override;

    [[nodiscard]] Statements expandWith(Expressions    subexpressions,
                                        Statements     substatements,
                                        lang::Context& new_context) const override;

  protected:
    void doBuild(CompileContext& context) override;

  private:
    lang::Identifier                              name_;
    Optional<lang::ResolvingHandle<lang::Entity>> type_opt_;
    lang::ResolvingHandle<lang::Entity>           type_;
    lang::Location                                type_location_;
    lang::Assigner                                assigner_;
    Optional<Owned<Expression>>                   assigned_;

    Optional<lang::ResolvingHandle<lang::Variable>> variable_ {};
};

#endif
