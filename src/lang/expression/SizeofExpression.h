#ifndef ANCE_SRC_LANG_EXPRESSION_SIZEOFEXPRESSION_H_
#define ANCE_SRC_LANG_EXPRESSION_SIZEOFEXPRESSION_H_

#include "DelayableExpression.h"

#include "lang/Element.h"

class Application;

/**
 * Gives the size of a value returned by an expression.
 */
class SizeofExpression
    : public DelayableExpression
    , public lang::Element<SizeofExpression, ANCE_CONSTRUCTS>
{
  public:
    /**
     * Create a new sizeof expression expression.
     * @param expression The expression to get the size of.
     * @param location The source location.
     */
    SizeofExpression(std::unique_ptr<Expression> expression, lang::Location location);

    [[nodiscard]] Expression& expression() const;

    [[nodiscard]] std::optional<lang::ResolvingHandle<lang::Type>> tryGetType() const override;

    bool validate(ValidationLogger& validation_logger) const override;

    [[nodiscard]] Expansion expandWith(Expressions subexpressions) const override;

  protected:
    void doBuild(CompileContext* context) override;

  private:
    std::unique_ptr<Expression>  expression_;
};

#endif