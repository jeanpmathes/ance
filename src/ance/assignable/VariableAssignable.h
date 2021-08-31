#ifndef ANCE_SRC_ANCE_ASSIGNABLE_VARIABLEASSIGNABLE_H_
#define ANCE_SRC_ANCE_ASSIGNABLE_VARIABLEASSIGNABLE_H_

#include "Assignable.h"
#include "ance/construct/value/Value.h"
#include "ance/scope/Scope.h"

/**
 * Represents an assignable variable.
 */
class VariableAssignable : public Assignable
{
  public:
    /**
     * Create a new VariableAssignable.
     * @param variable_identifier The identifier of the variable to assign.
     * @param location The source location.
     */
    explicit VariableAssignable(std::string variable_identifier, ance::Location location);

    void validate(ValidationLogger& validation_logger) override;

  protected:
    void setScope(ance::Scope* scope) override;
    void doBuild(CompileContext* context) override;

  private:
    std::string  variable_identifier_;
    ance::Scope* scope_ {nullptr};
};

#endif
