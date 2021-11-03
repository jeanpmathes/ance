#ifndef ANCE_SRC_ANCE_STATEMENT_LOCALVARIABLEDEFINITION_H_
#define ANCE_SRC_ANCE_STATEMENT_LOCALVARIABLEDEFINITION_H_

#include "Statement.h"

#include <optional>

#include "ance/Assigner.h"
#include "ance/construct/Variable.h"
#include "ance/utility/ResolvingHandle.h"

namespace ance
{
    class Type;
}

class Expression;

/**
 * Defines a local variable in the containing function.
 */
class LocalVariableDefinition : public Statement
{
  public:
    /**
     * Create a new local variable definition.
     * @param identifier The identifier of the variable.
     * @param type The type of the variable.
     * @param assigner The assigner to use for initial assignment.
     * @param assigned The initially assigned value.
     * @param location The source location.
     */
    LocalVariableDefinition(std::string                 identifier,
                            ance::Type*                 type,
                            Assigner                    assigner,
                            std::unique_ptr<Expression> assigned,
                            ance::Location              location);

    void setFunction(ance::Function* function) override;

    void validate(ValidationLogger& validation_logger) override;

  protected:
    void doBuild(CompileContext* context) override;

  private:
    std::string identifier_;
    ance::Type* type_;
    Assigner                    assigner_;
    std::unique_ptr<Expression> assigned_;

    std::optional<ance::ResolvingHandle<ance::Variable>> variable_ {};
};

#endif