#ifndef ANCE_SRC_ANCE_STATEMENT_LOCALREFERENCEVARIABLEDEFINITION_H_
#define ANCE_SRC_ANCE_STATEMENT_LOCALREFERENCEVARIABLEDEFINITION_H_

#include "Statement.h"

#include "ance/Assigner.h"

namespace ance
{
    class LocalVariable;
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
    static LocalReferenceVariableDefinition* defineReferring(std::string    identifier,
                                                             ance::Type*    type,
                                                             Expression*    value,
                                                             Application&   app,
                                                             ance::Location location);
    /**
     * Define a local variable referring to a given address.
     * @param address The address to refer to.
     * @return The created statement.
     */
    static LocalReferenceVariableDefinition* defineReferringTo(std::string    identifier,
                                                               ance::Type*    type,
                                                               Expression*    address,
                                                               ance::Location location);

  private:
    LocalReferenceVariableDefinition(std::string    identifier,
                                     ance::Type*    type,
                                     Expression*    reference,
                                     ance::Location location);

  public:
    void setFunction(ance::DefinedFunction* function) override;

    void validate(ValidationLogger& validation_logger) override;

    bool accept(ance::ApplicationVisitor& visitor) override;

  protected:
    void doBuild(CompileContext* context) override;

  private:
    std::string identifier_;
    ance::Type* type_;
    Expression* reference_;

    ance::LocalVariable* variable_ {nullptr};
};

#endif
