#ifndef ANCE_SRC_LANG_EXPRESSION_PARENTHESIS_H_
#define ANCE_SRC_LANG_EXPRESSION_PARENTHESIS_H_

#include "lang/expression/Expression.h"

/**
 * A parenthesis expression, which wraps an expression.
 */
class Parenthesis
    : public Expression
    , public lang::Element<Parenthesis, ANCE_CONSTRUCTS>
{
  public:
    /**
     * Create a new Parenthesis expression.
     * @param expression The expression to wrap in parenthesis.
     * @param location The location of the parenthesis.
     */
    Parenthesis(std::unique_ptr<Expression> expression, lang::Location location);

    [[nodiscard]] Expression& contained() const;

  public:
    bool isNamed() override;

    bool validate(ValidationLogger& validation_logger) const override;
    bool validateAssignment(const std::shared_ptr<lang::Value>& value,
                            lang::Location                      value_location,
                            ValidationLogger&                   validation_logger) override;

    [[nodiscard]] Expansion expandWith(Expressions subexpressions) const override;

    [[nodiscard]] std::optional<lang::ResolvingHandle<lang::Type>> tryGetType() const override;

    [[nodiscard]] std::shared_ptr<lang::Value> getValue() const override;

  protected:
    void doAssign(std::shared_ptr<lang::Value> value, CompileContext* context) override;

  private:
    std::unique_ptr<Expression> expression_;
};

#endif
