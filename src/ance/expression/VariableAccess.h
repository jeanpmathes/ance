#ifndef ANCE_SRC_ANCE_EXPRESSION_VARIABLEACCESS_H_
#define ANCE_SRC_ANCE_EXPRESSION_VARIABLEACCESS_H_

#include "DelayableExpression.h"

namespace ance
{
    class Variable;
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
     * @param identifier The identifier of the variable to access.
     * @param location The source location.
     */
    explicit VariableAccess(std::string identifier, ance::Location location);

  protected:
    void setScope(ance::Scope* scope) override;

  public:
    ance::Type* type() override;

    [[nodiscard]] bool isNamed() override;

    bool validate(ValidationLogger& validation_logger) override;
    bool validateAssignment(ance::Value*      value,
                            ance::Location    value_location,
                            ValidationLogger& validation_logger) override;

    bool accept(ance::ApplicationVisitor& visitor) override;

  protected:
    void doBuild(CompileContext* context) override;
    void doAssign(ance::Value* value, CompileContext* context) override;

  public:
    ~VariableAccess() override;

  private:
    std::string     identifier_;
    ance::Variable* variable_ {nullptr};
};

#endif