#ifndef ANCE_SRC_ANCE_EXPRESSION_VARIABLEACCESS_H_
#define ANCE_SRC_ANCE_EXPRESSION_VARIABLEACCESS_H_

#include "DelayableExpression.h"

namespace ance
{
    class Variable;
    class Scope;
}

/**
 * Access a variable and get its current value.
 */
class VariableAccess : public DelayableExpression
{
  public:
    /**
     * Create a new variable access.
     * @param identifier The identifier of the variable to access.
     * @param location The source location.
     */
    explicit VariableAccess(std::string identifier, ance::Location location);

  protected:
    void setScope(ance::Scope* scope) override;

  public:
    ance::Type* type() override;

    bool validate(ValidationLogger& validation_logger) override;

  protected:
    void doBuild(CompileContext* context) override;

  public:
    ~VariableAccess() override;

  private:
    std::string     identifier_;
    ance::Variable* variable_ {nullptr};
};

#endif