#ifndef ANCE_SRC_LANG_STATEMENT_LOCALVARIABLEDEFINITION_H_
#define ANCE_SRC_LANG_STATEMENT_LOCALVARIABLEDEFINITION_H_

#include "Statement.h"

#include <optional>

#include "lang/Assigner.h"
#include "lang/construct/Variable.h"
#include "lang/utility/ResolvingHandle.h"
#include "lang/Assigner.h"
#include "lang/Element.h"

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
     * @param identifier The identifier of the variable.
     * @param type The type of the variable.
     * @param type_location The location of the type.
     * @param assigner The assigner to use for initial assignment.
     * @param assigned The initially assigned value, or nullptr if a default value is used.
     * @param location The source location.
     */
    LocalVariableDefinition(std::string                       identifier,
                            lang::ResolvingHandle<lang::Type> type,
                            lang::Location                    type_location,
                            lang::Assigner                    assigner,
                            std::unique_ptr<Expression>       assigned,
                            lang::Location                    location);

    [[nodiscard]] const std::string&                identifier() const;
    [[nodiscard]] lang::ResolvingHandle<lang::Type> type() const;
    [[nodiscard]] lang::Assigner                    assigner() const;
    [[nodiscard]] Expression*                       assigned() const;

    void setScope(lang::Scope* scope) override;

    void validate(ValidationLogger& validation_logger) override;

  protected:
    void doBuild(CompileContext* context) override;

  private:
    std::string                       identifier_;
    lang::ResolvingHandle<lang::Type> type_;
    lang::Location                    type_location_;
    lang::Assigner                    assigner_;
    Expression*                       assigned_ptr_;
    std::unique_ptr<Expression>       assigned_;

    std::optional<lang::ResolvingHandle<lang::Variable>> variable_ {};
};

#endif