#ifndef ANCE_SRC_LANG_EXPRESSION_INDIRECTION_H_
#define ANCE_SRC_LANG_EXPRESSION_INDIRECTION_H_

#include "Expression.h"

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
    : public Expression
    , public lang::Element<Indirection, ANCE_CONSTRUCTS>
{
  public:
    /**
     * Create a new indirection.
     * @param expression The expression to access.
     * @param location The location of the indirection.
     */
    Indirection(Owned<Expression> expression, lang::Location location);

    [[nodiscard]] Expression const& value() const;

  public:
    bool validate(ValidationLogger& validation_logger) const override;

    [[nodiscard]] Expansion expandWith(Expressions subexpressions, lang::Context& new_context) const override;

  protected:
    void defineType(lang::ResolvingHandle<lang::Type> type) override;

  public:
    ~Indirection() override;

  private:
    Owned<Expression> value_;
};

#endif
