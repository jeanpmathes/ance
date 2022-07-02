#ifndef ANCE_SRC_LANG_EXPRESSION_INDIRECTION_H_
#define ANCE_SRC_LANG_EXPRESSION_INDIRECTION_H_

#include "DelayableExpression.h"

#include "lang/Element.h"
#include "lang/construct/Variable.h"
#include "lang/utility/ResolvingHandle.h"

namespace lang
{
    class Scope;
}
/**
 * The indirection operator is used to access indirect values, e.g. the value pointed to.
 */
class Indirection
    : public DelayableExpression
    , public lang::Element<Indirection, ANCE_CONSTRUCTS>
{
  public:
    /**
     * Create a new indirection.
     * @param expression The expression to access.
     * @param location The location of the indirection.
     */
    Indirection(std::unique_ptr<Expression> expression, lang::Location location);

    [[nodiscard]] Expression& value() const;

  public:
    [[nodiscard]] lang::ResolvingHandle<lang::Type> type() const override;

    bool validate(ValidationLogger& validation_logger) override;

    [[nodiscard]] Expansion expandWith(Expressions subexpressions) const override;

  protected:
    void doBuild(CompileContext* context) override;

  public:
    ~Indirection() override;

  private:
    std::unique_ptr<Expression> value_;
};

#endif
