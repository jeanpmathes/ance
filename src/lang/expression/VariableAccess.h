#ifndef ANCE_SRC_LANG_EXPRESSION_VARIABLEACCESS_H_
#define ANCE_SRC_LANG_EXPRESSION_VARIABLEACCESS_H_

#include "DelayableExpression.h"

#include "lang/Element.h"
#include "lang/construct/Variable.h"
#include "lang/utility/ResolvingHandle.h"

namespace lang
{
    class Scope;
}

/**
 * Access a variable and get or set its current value.
 */
class VariableAccess
    : public DelayableExpression
    , public lang::Element<VariableAccess, ANCE_CONSTRUCTS>
{
  public:
    /**
     * Create a new variable access.
     * @param variable The variable to access.
     * @param location The source location.
     */
    VariableAccess(lang::ResolvingHandle<lang::Variable> variable, lang::Location location);

    [[nodiscard]] lang::Variable const& variable() const;

  protected:
    void walkDefinitions() override;
    void postResolve() override;

  public:
    [[nodiscard]] bool isNamed() const override;

    bool validate(ValidationLogger& validation_logger) const override;
    bool validateAssignment(lang::Value const& value,
                            lang::Location     value_location,
                            ValidationLogger&  validation_logger) const override;

    [[nodiscard]] Expansion expandWith(Expressions subexpressions) const override;

  protected:
    void defineType(lang::ResolvingHandle<lang::Type>& type) override;
    void doBuild(CompileContext& context) override;
    void doAssign(Shared<lang::Value> value, CompileContext& context) override;

  private:
    bool isVariableDropped(ValidationLogger& validation_logger) const;

  public:
    ~VariableAccess() override;

  private:
    lang::ResolvingHandle<lang::Variable> variable_;
};

#endif
