#ifndef ANCE_SRC_ANCE_EXPRESSION_VARIABLEACCESS_H_
#define ANCE_SRC_ANCE_EXPRESSION_VARIABLEACCESS_H_

#include "DelayableExpression.h"

#include "lang/construct/Variable.h"
#include "lang/utility/ResolvingHandle.h"

namespace lang
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
    explicit VariableAccess(lang::ResolvingHandle<lang::Variable> variable, lang::Location location);

  protected:
    void setScope(lang::Scope* scope) override;

  public:
    lang::ResolvingHandle<lang::Type> type() override;

    [[nodiscard]] bool isNamed() override;

    bool validate(ValidationLogger& validation_logger) override;
    bool validateAssignment(const std::shared_ptr<lang::Value>& value,
                            lang::Location                      value_location,
                            ValidationLogger&                   validation_logger) override;

  protected:
    void doBuild(CompileContext* context) override;
    void doAssign(std::shared_ptr<lang::Value> value, CompileContext* context) override;

  public:
    ~VariableAccess() override;

  private:
    lang::ResolvingHandle<lang::Variable> variable_;
};

#endif