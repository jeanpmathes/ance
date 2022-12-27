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
    Parenthesis(Owned<Expression> expression, lang::Location location);

    [[nodiscard]] Expression const& contained() const;

  public:
    [[nodiscard]] bool isNamed() const override;

    bool validate(ValidationLogger& validation_logger) const override;
    bool validateAssignment(lang::Value const& value,
                            lang::Location     value_location,
                            ValidationLogger&  validation_logger) const override;

    [[nodiscard]] Expansion expandWith(Expressions subexpressions) const override;

    Shared<lang::Value>              getValue() override;
    [[nodiscard]] lang::Value const& getValue() const override;

  protected:
    void defineType(lang::ResolvingHandle<lang::Type>& type) override;
    void doAssign(Shared<lang::Value> value, CompileContext& context) override;

  private:
    Owned<Expression> expression_;
};

#endif
