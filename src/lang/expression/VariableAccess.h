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
     * @param is_defined Whether the variable is defined. If not, only write access is allowed.
     * @param location The source location.
     */
    VariableAccess(lang::ResolvingHandle<lang::Variable> variable, bool is_defined, lang::Location location);

    [[nodiscard]] lang::Variable const& variable() const;

  protected:
    void walkDefinitions() override;

  public:
    [[nodiscard]] bool isNamed() const override;

    bool validate(ValidationLogger& validation_logger) const override;
    bool validateAssignment(lang::Value const& value,
                            lang::Location     value_location,
                            ValidationLogger&  validation_logger) const override;

    [[nodiscard]] Expansion expandWith(Expressions subexpressions, lang::Context& new_context) const override;

  protected:
    void defineType(lang::ResolvingHandle<lang::Type> type) override;
    void doBuild(CompileContext& context) override;
    void doAssign(Shared<lang::Value> value, CompileContext& context) override;

  private:
    bool isVariableErased(ValidationLogger& validation_logger) const;

  public:
    ~VariableAccess() override;

  private:
    lang::ResolvingHandle<lang::Entity> variable_;
    bool                                is_defined_;
};

#endif
