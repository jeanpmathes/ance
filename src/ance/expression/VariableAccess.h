#ifndef ANCE_SRC_ANCE_EXPRESSION_VARIABLEACCESS_H_
#define ANCE_SRC_ANCE_EXPRESSION_VARIABLEACCESS_H_

#include "DelayableExpression.h"

#include "ance/construct/Variable.h"
#include "ance/utility/ResolvingHandle.h"

namespace ance
{
    class Scope;
}

/**
 * Access a variable and get or set its current value.
 */
class VariableAccess : public DelayableExpression
{
  public:
    /**
     * Create a new variable access.
     * @param variable The variable to access.
     * @param location The source location.
     */
    explicit VariableAccess(ance::ResolvingHandle<ance::Variable> variable, ance::Location location);

  protected:
    void setScope(ance::Scope* scope) override;

  public:
    ance::Type* type() override;

    [[nodiscard]] bool isNamed() override;

    bool validate(ValidationLogger& validation_logger) override;
    bool validateAssignment(const std::shared_ptr<ance::Value>& value,
                            ance::Location                      value_location,
                            ValidationLogger&                   validation_logger) override;

  protected:
    void doBuild(CompileContext* context) override;
    void doAssign(std::shared_ptr<ance::Value> value, CompileContext* context) override;

  public:
    ~VariableAccess() override;

  private:
    ance::ResolvingHandle<ance::Variable> variable_;
};

#endif