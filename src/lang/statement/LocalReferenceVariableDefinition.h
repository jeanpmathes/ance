#ifndef ANCE_SRC_LANG_STATEMENT_LOCALREFERENCEVARIABLEDEFINITION_H_
#define ANCE_SRC_LANG_STATEMENT_LOCALREFERENCEVARIABLEDEFINITION_H_

#include "Statement.h"

#include <optional>

#include "lang/Assigner.h"
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
class LocalReferenceVariableDefinition : public Statement
{
  public:
    /**
     * Define a local variable referring to another value.
     * @param value The value to refer.
     * @return The created statement.
     */
    static std::unique_ptr<LocalReferenceVariableDefinition> defineReferring(std::string identifier,
                                                                             lang::ResolvingHandle<lang::Type> type,
                                                                             lang::Location              type_location,
                                                                             std::unique_ptr<Expression> value,
                                                                             lang::Location              location);
    /**
     * Define a local variable referring to a given address.
     * @param address The address to refer to.
     * @return The created statement.
     */
    static std::unique_ptr<LocalReferenceVariableDefinition> defineReferringTo(std::string identifier,
                                                                               lang::ResolvingHandle<lang::Type> type,
                                                                               lang::Location type_location,
                                                                               std::unique_ptr<Expression> address,
                                                                               lang::Location              location);

  private:
    LocalReferenceVariableDefinition(std::string                       identifier,
                                     lang::ResolvingHandle<lang::Type> type,
                                     lang::Location                    type_location,
                                     std::unique_ptr<Expression>       reference,
                                     lang::Location                    location);

  public:
    void setFunction(lang::Function* function) override;

    void validate(ValidationLogger& validation_logger) override;

  protected:
    void doBuild(CompileContext* context) override;

  private:
    std::string                       identifier_;
    lang::ResolvingHandle<lang::Type> type_;
    lang::Location                    type_location_;
    std::unique_ptr<Expression>       reference_;

    std::optional<lang::ResolvingHandle<lang::Variable>> variable_ {};
};

#endif
