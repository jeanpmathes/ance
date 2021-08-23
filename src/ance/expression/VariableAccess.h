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
     */
    explicit VariableAccess(std::string identifier);

    void setScope(ance::Scope* scope) override;

    ance::Type* type() override;

    void buildValue(CompileContext* context) override;

    ~VariableAccess() override;

  private:
    std::string     identifier_;
    ance::Variable* variable_ {nullptr};
};

#endif