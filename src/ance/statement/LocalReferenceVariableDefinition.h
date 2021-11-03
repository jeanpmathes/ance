#ifndef ANCE_SRC_ANCE_STATEMENT_LOCALREFERENCEVARIABLEDEFINITION_H_
#define ANCE_SRC_ANCE_STATEMENT_LOCALREFERENCEVARIABLEDEFINITION_H_

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
class Application;

/**
 * Defines a local variable of reference type in the containing function.
 */
class LocalReferenceVariableDefinition : public Statement
{
  public:
    /**
     * Define a local variable referring to another value.
     * @param value The value to refer.
     * @return The created statement.
     */
    static LocalReferenceVariableDefinition* defineReferring(std::string                 identifier,
                                                             ance::Type*                 type,
                                                             std::unique_ptr<Expression> value,
                                                             ance::Location              location);
    /**
     * Define a local variable referring to a given address.
     * @param address The address to refer to.
     * @return The created statement.
     */
    static LocalReferenceVariableDefinition* defineReferringTo(std::string                 identifier,
                                                               ance::Type*                 type,
                                                               std::unique_ptr<Expression> address,
                                                               ance::Location              location);

  private:
    LocalReferenceVariableDefinition(std::string                 identifier,
                                     ance::Type*                 type,
                                     std::unique_ptr<Expression> reference,
                                     ance::Location              location);

  public:
    void setFunction(ance::Function* function) override;

    void validate(ValidationLogger& validation_logger) override;

  protected:
    void doBuild(CompileContext* context) override;

  private:
    std::string identifier_;
    ance::Type*                 type_;
    std::unique_ptr<Expression> reference_;

    std::optional<ance::ResolvingHandle<ance::Variable>> variable_ {};
};

#endif
