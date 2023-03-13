#ifndef ANCE_SRC_LANG_EXPRESSION_BINDREF_H_
#define ANCE_SRC_LANG_EXPRESSION_BINDREF_H_

#include "UnexpandedExpression.h"

#include <optional>

#include "lang/Element.h"

class Application;

class BindRef
    : public UnexpandedExpression
    , public lang::Element<BindRef, ANCE_CONSTRUCTS>
{
  public:
    /**
     * Creates a new bind reference.
     * @param value The value to bind.
     * @param location The location of the bind reference.
     */
    BindRef(Owned<Expression> value, lang::Location location);

  public:
    [[nodiscard]] Expression const& value() const;

    bool validate(ValidationLogger& validation_logger) const override;

    [[nodiscard]] Expansion expandWith(Expressions subexpressions, lang::Context& new_context) const override;

  protected:
    void defineType(lang::ResolvingHandle<lang::Type> type) override;

  public:
    ~BindRef() override;

  private:
    Owned<Expression> value_;
};

#endif
